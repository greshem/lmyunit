#include <stdlib.h>
//#include <MLmyUnit.hpp>
//#include <QzjUnit.hpp>
#include <unitlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string> 
//#include <dirent.h>
#include <fstream>
#include <iterator>  
#include <vector> 
#include <algorithm>
#include <iostream> 
#include <map>
#include <ext2fs/ext2fs.h>
using namespace std;

int ext2_super_block_dump(struct ext2_super_block in )	;

using namespace std;
void putChar( char *tmp, int size);
char *file_seek_and_read(FILE * file, int offset, int count, int * readLen);


char *file_seek64_and_read(FILE * file, int offset, int count, int * readLen)
{
	char *buffer;
	int ret;
	buffer=(char *)malloc(count);
	memset(buffer, '\0', count);
	lseek64(fileno(file), 0, SEEK_END);
	long long  length=lseek64(fileno(file), 0, SEEK_CUR);

	//请求的offset 大于文件的长度。 
	if( offset > length)
	{
		warn(" offset is larger than fileSize %d", length);
		return NULL;
	}

	//在文件末尾的时候, 读取的字节会< count. 	
	if(length -offset < count)
	{
		fseek(file, offset, SEEK_SET);
		//写成  fread(tmp, sizeof(tmp), 1 , file)返回 读取了几个结构
		ret=fread(buffer, 1, count,   file);
		if(ret != count)
		{
			warn(" read length not correct \n");
		}
		//*readLen=ret;	
		*readLen=ret;
		return buffer;
	}
	else
	{
		fseek(file, offset, SEEK_SET);
		ret=fread(buffer, 1,count, file);
		if(ret != count)
		{
			warn(" read length not correct \n");
		}
		//putChar(tmp, count);
		*readLen=ret;
		return buffer;
	}	
}



int main(int argc, char *argv[])
{
	FILE *file;
	ext2_super_block ext2;
	assert(sizeof(ext2)==1024);
	char *sb;
	if(argc != 2)
	{
		die("Usage: %s /dev/device", argv[0]);
	}
	file=fopen(argv[1] , "r");
	if(file==NULL)
	{
		die("open file %s", argv[0]);
	}
	int readLen;
	char *data= file_seek_and_read(file, 1024, 1024, &readLen);
	memcpy((char*)&ext2, data, 1024);
	//printf("%d ", ext2->s_inodes_count);
	ext2_super_block_dump(  ext2 )	;


}

// 位移到文件的某个位置 读取一定长度的 数据。 
char *file_seek_and_read(FILE * file, int offset, int count, int * readLen)
{
	char *buffer;
	int ret;
	buffer=(char *)malloc(count);
	fseek(file, 0, SEEK_END);
	long  length=ftell(file);

	//请求的offset 大于文件的长度。 
	if( offset > length)
	{
		warn(" offset is larger than fileSize %d", length);
		return NULL;
	}

	//在文件末尾的时候, 读取的字节会< count. 	
	if(length -offset < count)
	{
		fseek(file, offset, SEEK_SET);
		//写成  fread(tmp, sizeof(tmp), 1 , file)返回 读取了几个结构
		ret=fread(buffer, 1, count,   file);
		if(ret != count)
		{
			warn(" read length not correct \n");
		}
		//*readLen=ret;	
		*readLen=ret;
		return buffer;
	}
	else
	{
		fseek(file, offset, SEEK_SET);
		ret=fread(buffer, 1,count, file);
		if(ret != count)
		{
			warn(" read length not correct \n");
		}
		//putChar(tmp, count);
		*readLen=ret;
		return buffer;
	}	
}

#include <ext2fs/ext2fs.h>
using namespace std;

int ext2_super_block_dump(struct ext2_super_block in )	
{
	cout<< "s_inodes_count		"<< in.s_inodes_count<<endl;
	cout<< "s_blocks_count		"<< in.s_blocks_count<<endl;
	cout<< "s_r_blocks_count		"<< in.s_r_blocks_count<<endl;
	cout<< "s_free_blocks_count		"<< in.s_free_blocks_count<<endl;
	cout<< "s_free_inodes_count		"<< in.s_free_inodes_count<<endl;
	cout<< "s_first_data_block		"<< in.s_first_data_block<<endl;
	cout<< "s_log_block_size		"<< in.s_log_block_size<<endl;
	cout<< "s_log_frag_size		"<< in.s_log_frag_size<<endl;
	cout<< "s_blocks_per_group		"<< in.s_blocks_per_group<<endl;
	cout<< "s_frags_per_group		"<< in.s_frags_per_group<<endl;
	cout<< "s_inodes_per_group		"<< in.s_inodes_per_group<<endl;
	cout<< "s_mtime		"<< ctime((time_t*)&(in.s_mtime))<<endl;
	cout<< "s_wtime		"<< ctime((time_t*)&(in.s_wtime))<<endl;
	cout<< "s_mnt_count		"<< in.s_mnt_count<<endl;
	cout<< "s_max_mnt_count		"<< in.s_max_mnt_count<<endl;
	cout<< "s_magic		"<< in.s_magic<<endl;
	cout<< "s_state		"<< in.s_state<<endl;
	cout<< "s_errors		"<< in.s_errors<<endl;
	cout<< "s_minor_rev_level		"<< in.s_minor_rev_level<<endl;
	cout<< "s_lastcheck		"<<ctime((time_t*) &in.s_lastcheck)<<endl;
	cout<< "s_checkinterval		"<< in.s_checkinterval<<endl;
	cout<< "s_creator_os		"<< in.s_creator_os<<endl;
	cout<< "s_rev_level		"<< in.s_rev_level<<endl;
	cout<< "s_def_resuid		"<< in.s_def_resuid<<endl;
	cout<< "s_def_resgid		"<< in.s_def_resgid<<endl;
	cout<< "s_first_ino		"<< in.s_first_ino<<endl;
	cout<< "s_inode_size		"<< in.s_inode_size<<endl;
	cout<< "s_block_group_nr		"<< in.s_block_group_nr<<endl;
	cout<< "s_feature_compat		"<< in.s_feature_compat<<endl;
	cout<< "s_feature_incompat		"<< in.s_feature_incompat<<endl;
	cout<< "s_feature_ro_compat		"<< in.s_feature_ro_compat<<endl;
	cout<< "s_uuid[16]		"<< in.s_uuid[16]<<endl;
	cout<< "s_volume_name[16]		"<< string(in.s_volume_name)<<endl;
	cout<< "s_last_mounted[64]		"<< string(in.s_last_mounted)<<endl;
	cout<< "s_algorithm_usage_bitmap		"<< in.s_algorithm_usage_bitmap<<endl;
	cout<< "s_prealloc_blocks		"<< in.s_prealloc_blocks<<endl;
	cout<< "s_prealloc_dir_blocks		"<< in.s_prealloc_dir_blocks<<endl;
	cout<< "s_reserved_gdt_blocks		"<< in.s_reserved_gdt_blocks<<endl;
	cout<< "s_journal_uuid[16]		"<< in.s_journal_uuid[16]<<endl;
	cout<< "s_journal_inum		"<< in.s_journal_inum<<endl;
	cout<< "s_journal_dev		"<< in.s_journal_dev<<endl;
	cout<< "s_last_orphan		"<< in.s_last_orphan<<endl;
	cout<< "s_hash_seed[4]		"<< in.s_hash_seed[4]<<endl;
	cout<< "s_def_hash_version		"<< in.s_def_hash_version<<endl;
	cout<< "s_jnl_backup_type		"<< in.s_jnl_backup_type<<endl;
	cout<< "s_desc_size		"<< in.s_desc_size<<endl;
	cout<< "s_default_mount_opts		"<< in.s_default_mount_opts<<endl;
	cout<< "s_first_meta_bg		"<< in.s_first_meta_bg<<endl;
	cout<< "s_mkfs_time		"<< ctime((time_t*)&in.s_mkfs_time)<<endl;
	cout<< "s_jnl_blocks[17]		"<< in.s_jnl_blocks[17]<<endl;
	cout<< "s_blocks_count_hi		"<< in.s_blocks_count_hi<<endl;
	cout<< "s_r_blocks_count_hi		"<< in.s_r_blocks_count_hi<<endl;
	cout<< "s_free_blocks_hi		"<< in.s_free_blocks_hi<<endl;
	cout<< "s_min_extra_isize		"<< in.s_min_extra_isize<<endl;
	cout<< "s_want_extra_isize		"<< in.s_want_extra_isize<<endl;
	cout<< "s_flags		"<< in.s_flags<<endl;
	cout<< "s_raid_stride		"<< in.s_raid_stride<<endl;
	cout<< "s_mmp_interval		"<< in.s_mmp_interval<<endl;
	cout<< "s_mmp_block		"<< in.s_mmp_block<<endl;
	cout<< "s_raid_stripe_width		"<< in.s_raid_stripe_width<<endl;
	cout<< "s_log_groups_per_flex		"<< in.s_log_groups_per_flex<<endl;
	cout<< "s_reserved_char_pad		"<< in.s_reserved_char_pad<<endl;
	cout<< "s_reserved_pad		"<< in.s_reserved_pad<<endl;
	cout<< "s_kbytes_written		"<< in.s_kbytes_written<<endl;
	cout<< "s_reserved[160]		"<< in.s_reserved[160]<<endl;
}


