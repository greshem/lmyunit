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
//#2010_08_24_11:30:17 add by qzj
using namespace std;
TEST(base, MFile)
{
	EXPECT_EQ(1, 1);
	// MString str("MFile.cpp");
	// MFile file;
	// file.Create("bbb.txt");
	// for(int i=0; i<=100;i++)
	// {
	// 	MString tree(RandFilePath(6).c_str());	
	// 	file.WriteString(tree);
	// 	cout<<tree.c_str()<<endl;
	// 	cout<<tree.basename().c_str()<<endl;
	// 	//MFile::CreateDirectoryTree(tree);
	// 	//file.WriteString(RandFilePath(6).c_str());	
	// }
	// file.Close();
}


TEST(fseek, MFILE)
{
	MFile file;
	file.Create("10240.txt");
	file.SetFileLength(10240);
	EXPECT_EQ(file.GetFileLength(), 10240);	
	//往前1024
	file.Seek(1024, SEEK_SET)	;
	EXPECT_EQ(file.GetCurOffset(), 1024);

	//再往前1024	
	file.Seek(1024, SEEK_CUR)	;
	EXPECT_EQ(file.GetCurOffset(), 1024*2);
	
	file.Seek(0, SEEK_END)	;
	EXPECT_EQ(file.GetCurOffset(), 10240);

	file.Seek(1024, SEEK_SET)	;
	EXPECT_EQ(file.GetCurOffset(), 1024);
	file.Close();;


	EXPECT_EQ(filesize("10240.txt"), 10240);
	
	MFile file2;
	file.Open("10240.txt");
	EXPECT_EQ(file.GetCurOffset(), 0);
	
	//100次也是0偏移
	for(int i=0; i<=100; i++)
	{
		file.Seek(0, SEEK_CUR);
		EXPECT_EQ(file.GetCurOffset(), 0);
	}
	//seek(length, SEEK_END)之后， 会增大文件大小length , 但是 文件的大小还是 不变。
	file.Seek(10240, SEEK_END);
	EXPECT_EQ(file.GetCurOffset(), 10240*2);

	EXPECT_EQ(file.GetCurOffset(), 10240*2);
	EXPECT_EQ(file.Seek(0,SEEK_CUR), 10240*2);
	
	//0, SEEK_CUR, 当前的offset 大于文件的长度。 , 文件什么都没写
	EXPECT_EQ(file.Seek(0,SEEK_END), 10240);
	EXPECT_EQ(file.GetFileLength(), 10240);
	file.Close();
	//EXPECT_EQ(file.GetFileLength(), 10240*2);
	
	EXPECT_EQ(filesize("10240.txt"), 10240);
	//EXPECT_EQ( );
}

TEST(write, MFILE)
{
	unlink("10240.txt");
	
	MFile file;
	file.Create("10240.txt");
	file.Seek(10239, SEEK_END);
	EXPECT_EQ(file.GetCurOffset(), 10239);	
	EXPECT_EQ(file.GetFileLength(), 0);	
	
	file.Seek(10239, SEEK_SET);
	file.Write("a", 1);

	//只有写了东西下面的两个数值才会一样。
	EXPECT_EQ(file.GetCurOffset(), 10240);	
	EXPECT_EQ(file.GetFileLength(),10240);	
	file.Close();
	
		

}

TEST(no_write, MFILE)
{
	unlink("10240.txt");
	
	MFile file;
	file.Create("10240.txt");
	file.Seek(10239, SEEK_END);
	EXPECT_EQ(file.GetCurOffset(), 10239);	
	EXPECT_EQ(file.GetFileLength(), 0);	
	
	file.Seek(10239, SEEK_SET);

	//只有写了东西下面的两个数值才会一样。
	EXPECT_EQ(file.GetCurOffset(), 10239);	
	EXPECT_EQ(file.GetFileLength(),0);	
	
		
	file.Close();

}

char mbr[512];
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

