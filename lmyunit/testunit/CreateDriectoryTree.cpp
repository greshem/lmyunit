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
#include <gtest/gtest.h>

using namespace std;

char mbr[512];
TEST(CreateDir, MFile)
{
	MString str("MFile.cpp");
	MFile file;
	for(int i=0; i<=100;i++)
	{
		cout<<"---------------------"<<endl;
		MString fileName(RandFilePath(6).c_str());	
		//mkdir -p 暂时注释掉, 否则老是产生一大堆的目录.
		//MFile::CreateDirectoryTree(fileName.basename());
		//echo  >> file
		file.Create(fileName);
		file.WriteString(fileName);	
		file.Close();
	
	}
	file.Close();
	cout<<str.c_str()<<endl;
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

