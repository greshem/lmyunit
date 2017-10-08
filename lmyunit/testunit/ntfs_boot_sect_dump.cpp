#include  <unitlib.h>
#include <gtest/gtest.h>
#include <fstream>
//#include <dirent.h>
#include <string> 
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unitlib.h>
#include <map>
#include <iostream> 
#include <algorithm>
#include <vector> 
#include <iterator>  
using namespace std;
//##include "type_def.txt"

typedef unsigned char   u8;                    /* Unsigned types of an exact size */
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned long long  u64;
typedef unsigned long long  int_64;
typedef char   s8;                     /* Signed types of an exact size */
typedef short  s16;
typedef int  s32;
typedef long long  s64;
typedef u16 le16;
typedef u32 le32;
typedef u64 le64;
//#include "ntfs_struct.txt"
struct ntfs_boot_sector {
        char  jump[3];                    /* Irrelevant (jump to boot up code).*/
        u64 oem_id;                     /* Magic "NTFS    ". */
        u16 bytes_per_sector;           /* Size of a sector in bytes. */
        u8  sectors_per_cluster;        /* Size of a cluster in sectors. */
        u16 reserved_sectors;           /* zero */
        u8  fats;                       /* zero */
        u16 root_entries;               /* zero */
        u16 sectors;                    /* zero */
        u8  media_type;                 /* 0xf8 = hard disk */
        u16 sectors_per_fat;            /* zero */
		u16 sectors_per_track;          /* Required to boot Windows. */
		u16 heads;                      /* Required to boot Windows. */
		u32 hidden_sectors;             /* Offset to the start of   relative to the disk in sectors. Required to boot Windows. */
		u32 large_sectors;              /* zero */

        u8 physical_drive;              /* 0x00 floppy, 0x80 hard disk */
        u8 current_head;                /* zero */
        u8 extended_boot_signature;     /* 0x80 */
        u8 reserved2;                   /* zero */
		int_64 number_of_sectors;          /* Number of sectors in volume. Gives maximum volume size of 2^63 sectors.  Assuming standard sector size of 512 bytes, the maximum byte size is approx. 4.7x10^21 bytes. (-; */ 
		int_64 mft_lcn;                    /* Cluster location of mft data. */
        int_64 mftmirr_lcn;                /* Cluster location of copy of mft. */
        s8  clusters_per_mft_record;    /* Mft record size in clusters. */
        u8  reserved0[3];               /* zero */
        s8  clusters_per_index_record;  /* Index block size in clusters. */
        u8  reserved1[3];               /* zero */
        u64 volume_serial_number;       /* Irrelevant (serial number). */
        u32 checksum;                   /* Boot sector checksum. */
		u8  bootstrap[426];             /* Irrelevant (boot up code). */
        u16 end_of_sector_marker;       /* End of bootsector magic. Always is
                                           0xaa55 in little endian. */
/* sizeof() = 512 (0x200) bytes */
} __attribute__((__packed__)) NTFS_BOOT_SECTOR;
int ntfs_boot_sector_dump(struct ntfs_boot_sector in )	
{
	cout<< "u8	jump[3]		"<< in.jump[3]<<endl;
	cout<< "u64	oem_id		"<< in.oem_id<<endl;
	cout<< "u16	bytes_per_sector		"<< in.bytes_per_sector<<endl;
	cout<< "u8	sectors_per_cluster		"<< in.sectors_per_cluster<<endl;
	cout<< "u16	reserved_sectors		"<< in.reserved_sectors<<endl;
	cout<< "u8	fats		"<< in.fats<<endl;
	cout<< "u16	root_entries		"<< in.root_entries<<endl;
	cout<< "u16	sectors		"<< in.sectors<<endl;
	cout<< "u8	media_type		"<< in.media_type<<endl;
	cout<< "u16	sectors_per_fat		"<< in.sectors_per_fat<<endl;
	cout<< "u16	sectors_per_track		"<< in.sectors_per_track<<endl;
	cout<< "u16	heads		"<< in.heads<<endl;
	cout<< "u32	hidden_sectors		"<< in.hidden_sectors<<endl;
	cout<< "u32	large_sectors		"<< in.large_sectors<<endl;
	cout<< "u8	physical_drive		"<< in.physical_drive<<endl;
	cout<< "u8	current_head		"<< in.current_head<<endl;
	cout<< "u8	extended_boot_signature		"<< in.extended_boot_signature<<endl;
	cout<< "u8	reserved2		"<< in.reserved2<<endl;
	cout<< "int_64	number_of_sectors		"<< in.number_of_sectors<<endl;
	cout<< "int_64	mft_lcn		"<< in.mft_lcn<<endl;
	cout<< "int_64	mftmirr_lcn		"<< in.mftmirr_lcn<<endl;
	cout<< "s8	clusters_per_mft_record		"<< in.clusters_per_mft_record<<endl;
	cout<< "u8	reserved0[3]		"<< in.reserved0[3]<<endl;
	cout<< "s8	clusters_per_index_record		"<< in.clusters_per_index_record<<endl;
	cout<< "u8	reserved1[3]		"<< in.reserved1[3]<<endl;
	cout<< "u64	volume_serial_number		"<< in.volume_serial_number<<endl;
	cout<< "u32	checksum		"<< in.checksum<<endl;
	cout<< "u8	bootstrap[426]		"<< in.bootstrap[426]<<endl;
	cout<< "u16	end_of_sector_marker		"<< in.end_of_sector_marker<<endl;
}
int main(int argc, char *argv[])
{
	
	FILE *file;
	struct ntfs_boot_sector in;
	assert(sizeof(in)==512);
	char *sb;
	
	if(argc != 2)
	{
		die("Usage: %s /dev/ntfs_device", argv[0]);
	}
	file=fopen(argv[1], "r");
	if(file==NULL)
	{
		die("open file %s", argv[1]);
	}
	int readLen;
	char *data= file_seek64_and_read(file, 0, 512, &readLen);
	memcpy((char*)&in, data, 512);
	//printf("%d ", ext2->s_inodes_count);
	char oem[8];
	memcpy(oem, &(in.oem_id), 8);
	if(oem[0]=='N' && oem[1]=='T' && oem[2]=='F' && oem[3]=='S')
	{
		ntfs_boot_sector_dump(in);
	}
	else
	{
		cout<<"不是微软格式的ntfs  分区"<<endl;		
	}
	
	return 0;
}
