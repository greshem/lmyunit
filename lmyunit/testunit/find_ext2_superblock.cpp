/***************************************************
* Description - 对于当前的块设备找出ext2ext3 超级快。  
* Author -      qianzhongjie@gmail.com
* Date -        2010_08_04_10:42:36
* *************************************************/
#include <stdlib.h>
#include <unitlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string> 
#include <fstream>
#include <iterator>  
#include <vector> 
#include <algorithm>
#include <iostream> 
#include <map>

typedef unsigned int __u32;
typedef unsigned int __s32;
typedef unsigned short __u16;
typedef unsigned short __s16;
typedef unsigned char __u8;
/*
 * Structure of the super block
 */
struct ext2_super_block {
        __u32   s_inodes_count;         /* Inodes count */
        __u32   s_blocks_count;         /* Blocks count */
        __u32   s_r_blocks_count;       /* Reserved blocks count */
        __u32   s_free_blocks_count;    /* Free blocks count */
        __u32   s_free_inodes_count;    /* Free inodes count */
        __u32   s_first_data_block;     /* First Data Block */
        __u32   s_log_block_size;       /* Block size */
        __s32   s_log_frag_size;        /* Fragment size */
        __u32   s_blocks_per_group;     /* # Blocks per group */
        __u32   s_frags_per_group;      /* # Fragments per group */
        __u32   s_inodes_per_group;     /* # Inodes per group */
        __u32   s_mtime;                /* Mount time */
        __u32   s_wtime;                /* Write time */
        __u16   s_mnt_count;            /* Mount count */
        __s16   s_max_mnt_count;        /* Maximal mount count */
        __u16   s_magic;                /* Magic signature */
        __u16   s_state;                /* File system state */
        __u16   s_errors;               /* Behaviour when detecting errors */
        __u16   s_minor_rev_level;      /* minor revision level */
        __u32   s_lastcheck;            /* time of last check */
        __u32   s_checkinterval;        /* max. time between checks */
        __u32   s_creator_os;           /* OS */
        __u32   s_rev_level;            /* Revision level */
        __u16   s_def_resuid;           /* Default uid for reserved blocks */
        __u16   s_def_resgid;           /* Default gid for reserved blocks */
        /*
         * These fields are for EXT2_DYNAMIC_REV superblocks only.
         *
         * Note: the difference between the compatible feature set and
         * the incompatible feature set is that if there is a bit set
         * in the incompatible feature set that the kernel doesn't
         * know about, it should refuse to mount the filesystem.
         *
         * e2fsck's requirements are more strict; if it doesn't know
         * about a feature in either the compatible or incompatible
         * feature set, it must abort and not try to meddle with
         * things it doesn't understand...
         */
        __u32   s_first_ino;            /* First non-reserved inode */
        __u16   s_inode_size;           /* size of inode structure */
        __u16   s_block_group_nr;       /* block group # of this superblock */
        __u32   s_feature_compat;       /* compatible feature set */
        __u32   s_feature_incompat;     /* incompatible feature set */
        __u32   s_feature_ro_compat;    /* readonly-compatible feature set */
        __u8    s_uuid[16];             /* 128-bit uuid for volume */
        char    s_volume_name[16];      /* volume name */
        char    s_last_mounted[64];     /* directory where last mounted */
        __u32   s_algorithm_usage_bitmap; /* For compression */
        /*
         * Performance hints.  Directory preallocation should only
         * happen if the EXT2_FEATURE_COMPAT_DIR_PREALLOC flag is on.
         */
        __u8    s_prealloc_blocks;      /* Nr of blocks to try to preallocate*/
        __u8    s_prealloc_dir_blocks;  /* Nr to preallocate for dirs */
        __u16   s_reserved_gdt_blocks;  /* Per group table for online growth */
        /*
         * Journaling support valid if EXT2_FEATURE_COMPAT_HAS_JOURNAL set.
         */
        __u8    s_journal_uuid[16];     /* uuid of journal superblock */
        __u32   s_journal_inum;         /* inode number of journal file */
        __u32   s_journal_dev;          /* device number of journal file */
        __u32   s_last_orphan;          /* start of list of inodes to delete */
        __u32   s_hash_seed[4];         /* HTREE hash seed */
        __u8    s_def_hash_version;     /* Default hash version to use */
        __u8    s_jnl_backup_type;      /* Default type of journal backup */
        __u16   s_reserved_word_pad;
        __u32   s_default_mount_opts;
        __u32   s_first_meta_bg;        /* First metablock group */
        __u32   s_mkfs_time;            /* When the filesystem was created */
        __u32   s_jnl_blocks[17];       /* Backup of the journal inode */
        __u32   s_reserved[172];        /* Padding to the end of the block */
};

MLogFile logger;
using namespace std;
int main(int argc, char *argv[])
{
	
	cout<<"sizeof(sb)"<<sizeof(ext2_super_block)<<endl;
	int skiprate=512;               /* one sector */
        loff_t sk=0, skl=0;
        int fd;
        char *s;
        time_t tm, last = time(0);
        loff_t interval = 1024 * 1024;

        struct ext2_super_block ext2;
        /* interesting fields: EXT2_SUPER_MAGIC
         *      s_blocks_count s_log_block_size s_mtime s_magic s_lastcheck */

#ifdef ENABLE_NLS
        setlocale(LC_MESSAGES, "");
        setlocale(LC_CTYPE, "");
        bindtextdomain(NLS_CAT_NAME, LOCALEDIR);
        textdomain(NLS_CAT_NAME);
#endif
        if (argc<2) {
                fprintf(stderr,
                        "Usage:  findsuper device [skipbytes [startkb]]\n" );
                exit(0);
        }
        if (argc>2)
                skiprate = strtol(argv[2], &s, 0);
        if (s == argv[2]) {
                fprintf(stderr,("skipbytes should be a number, not %s\n"), s);
                exit(1);
        }
        if (skiprate & 0x1ff) {
                fprintf(stderr,
                        ("skipbytes must be a multiple of the sector size\n"));
                exit(2);
        }
        if (argc>3)
                sk = skl = strtoll(argv[3], &s, 0) << 10;
        if (s == argv[3]) {
                fprintf(stderr,("startkb should be a number, not %s\n"), s);
                exit(1);
        }
        if (sk < 0) {
                fprintf(stderr,("startkb should be positive, not %Ld\n"), sk);
                exit(1);
        }
        fd = open(argv[1], O_RDONLY);
        if (fd < 0) {
                perror(argv[1]);
                exit(1);
        }
 
        /* Now, go looking for the superblock! */
        printf(("starting at %Ld, with %d byte increments\n"), sk, skiprate);
        printf(("       thisoff     block fs_blk_sz  blksz grp last_mount\n"));
        for (; lseek64(fd, sk, SEEK_SET) != -1 &&
               read(fd, &ext2, 512) == 512; sk += skiprate) {

                if (sk && !(sk & (interval - 1))) {
                        time_t now, diff;

                        now = time(0);
                        diff = now - last;

                        if (diff > 0) {
                                s = ctime(&now);
                                s[24] = 0;
                                printf("\r%14Ld: %8LdkB/s @ %s", sk,
                                       (((sk - skl)) / diff) >> 10, s);
                                fflush(stdout);
                        }
                        if (diff < 5)
                                interval <<= 1;
                        else if (diff > 20)
                                interval >>= 1;
                        last = now;
                        skl = sk;
                }
	#define EXT2_SUPER_MAGIC        0xEF53
	#define WHY			printf
                if (ext2.s_magic != EXT2_SUPER_MAGIC)
                        continue;
                if (ext2.s_log_block_size > 4)
                        WHY("log block size > 4 (%u)\n", ext2.s_log_block_size);
                if (ext2.s_r_blocks_count > ext2.s_blocks_count)
                        WHY("r_blocks_count > blocks_count (%u > %u)\n",
                            ext2.s_r_blocks_count, ext2.s_blocks_count);
                if (ext2.s_free_blocks_count > ext2.s_blocks_count)
                        WHY("free_blocks_count > blocks_count\n (%u > %u)\n",
                            ext2.s_free_blocks_count, ext2.s_blocks_count);
                if (ext2.s_free_inodes_count > ext2.s_inodes_count)
                        WHY("free_inodes_count > inodes_count (%u > %u)\n",
                            ext2.s_free_inodes_count, ext2.s_inodes_count);

                tm = ext2.s_mtime;
                s=ctime(&tm);
                s[24]=0;
                printf("\r%14Ld %9Ld %9d %5d %4d %s\n",
                       sk, sk >> 10, ext2.s_blocks_count,
                       1 << (ext2.s_log_block_size + 10),
                       ext2.s_block_group_nr, s);
        }
        printf(("\n%14Ld: finished with errno %d\n"), sk, errno);
        close(fd);

        return errno;

}
