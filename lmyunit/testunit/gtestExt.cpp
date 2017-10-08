#include <stdlib.h>


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
#include "../fileSystem/ExtFileSystem.hpp"
#include "../fileSystem/ExtFileSystem.cpp"

//2010_08_20 by qzj. 


MLogFile logger;
using namespace std;
int main(int argc, char *argv[])
{

	MString str("main.cpp");
	logger.Instance(MString(argv[0])+".log", 1000);
	logger.WriteError("test", "test");

	ExtFileSystem  extfs;
	extfs.fs_open("/dev/ram0");

	dump_image_head(extfs.initial_image_hdr());
	extfs.setupbitmap();
	// cout<<"block_size->"<<extfs.block_size()<<endl;;;
	// cout<<"device_size->"<<extfs.device_size()<<endl;
	// cout<<"block_count->"<<extfs.block_count()<<endl;
	extfs.fs_close();
//	ntfs.
	return 0;
}

