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
#include <gtest/gtest.h>
//2010_06_29 by qzj. 
//#2010_08_24_10:50:13 add by qzj
//gtest
//
char mbr[512];
using namespace std;


TEST(CreateDir, mfile)
//int test1()
{
	MFile file;
	string content;
	srandom(getpid());
	for(int i=0; i<=1000;i++)
#ifdef WINDOWSCODE
	srand();
#else
	srandom(getpid());
#endif
	for(int i=0; i<=1000;i++)
	{
		MString fileName(RandFilePath(6).c_str());	
		MFile::CreateDirectoryTree(fileName.dirname());
		if( ! MFile::IsExist(fileName))
		{
			file.Create(fileName);
			file.WriteString(fileName);	
			file.Close();
			EXPECT_EQ(MFile::IsExist(fileName),1);

			file_get_content(string(fileName.c_str()), content);		
			EXPECT_EQ(fileName.Length()+1, filesize(fileName.c_str()) ) ;
		}
		else
		{
			cout<<"file exist "<<endl;
		}
	
	}
	file.Close();
	cout<<"MFile.cpp"<<endl;
}

TEST(endian , size)
{
	EXPECT_EQ( sizeof(mbr), 512 );
	EXPECT_EQ( sizeof(int), 4 );
	EXPECT_EQ( sizeof(long), 4 );
	EXPECT_EQ( sizeof(long long ), 8 );
}

TEST(fat, info)
{
	EXPECT_EQ((1-1) ,0);
	
}
int main(int argc, char * argv[])
{
	testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}

