//###################################################
//#include <QzjUnit.hpp>
#include <unitlib.h>
#include <algorithm>
//#include <dirent.h>
//#include <dirent.h>
#include <ext2fs/ext2fs.h>
#include <fstream>
#include <iostream>
#include <iostream> 
#include <iterator>  
#include <map>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <string> 
#include <vector> 

int main()
{
	ext2_filsys fs;
	int ret;
	int use_superblock=0;
	int use_blocksize=0;
	int flags=EXT2_FLAG_JOURNAL_DEV_OK| EXT2_FLAG_SOFTSUPP_FEATURES;
	ret=ext2fs_open("/dev/sda1", flags, use_superblock, use_blocksize, unix_io_manager, &fs);
	if(ret)
	{
		die("file superblock error\n");
	}	
	cout<<fs->super->s_max_mnt_count<<endl;
}
