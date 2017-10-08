#include <fstream>
#include <dirent.h>
#include <string> 
#include <iostream>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include <QzjUnit.hpp>
//#include <MLmyUnit.hpp>
#include <Baselib.hpp>
#include <map>
#include <iostream> 
#include <algorithm>
#include <vector> 
#include <iterator>  
#include <stdlib.h>
// check  ret hardisk have as least  [[size]]  byte free space . 
// ret 是传入的磁盘的fd 好， 
// size 要求的磁盘大小
#include <sys/statvfs.h>
extern void check_free_space(int* ret, unsigned long long size)
{


    unsigned long long dest_size;
    struct statvfs stvfs;
    struct stat stat;
    int debug = 1;

    if (fstatvfs(*ret, &stvfs) == -1) 
	{
        printf("WARNING: Unknown free space on the destination: %s\n",
        strerror(errno));
        return;
    }
    /* if file is a FIFO there is no point in checking the size */
    if (!fstat(*ret, &stat)) 
	{
        if (S_ISFIFO(stat.st_mode))
            return;
    } else 
	{
        printf("WARNING: Couldn't get file info because of the following error: %s\n",
        strerror(errno));
    }

    dest_size = (unsigned long long)stvfs.f_frsize * stvfs.f_bfree;
    if (!dest_size)
	{
            dest_size = (unsigned long long)stvfs.f_bsize * stvfs.f_bfree;
	}

    if (dest_size < size)
	{
			//程序die. 
            //log_mesg(0, 1, 1, debug, "Destination doesn't have enough free space: %llu MB < %llu MB\n", print_size(dest_size, MBYTE), print_size(size, MBYTE));
            cout<<"error size is small"<<endl;
	}
//            log_mesg(0, 1, 1, debug, "Destination doesn't have enough free space: %llu MB < %llu MB\n", dest_size, size);
}
int main()
{
	int fd=open("/dev/sdb1", O_RDONLY);
	if(fd == -1)
	{
		die<char>("open sda1 faile , is devicd exist \n");	
	}
	int size=1024*1024*1024;
	check_free_space(&fd, size);
	
}
