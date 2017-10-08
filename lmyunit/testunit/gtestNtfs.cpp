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
#include "../fileSystem/NtfsFileSystem.hpp"
#include "../fileSystem/NtfsFileSystem.cpp"

//2010_08_20 by qzj. 


MLogFile logger;
using namespace std;
int main(int argc, char *argv[])
{

	MString str("main.cpp");
	logger.Instance(MString(argv[0])+".log", 1000);
	logger.WriteError("test", "test");

	NtfsFileSystem ntfs;
	ntfs.fs_open("/dev/ram0");
	image_head tmp=ntfs.initial_image_hdr();
	ntfs.fs_close();
//	ntfs.
	return 0;
}

