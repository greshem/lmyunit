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
//2010_08_23 by qzj. 
//ini �ļ�����ʽ���漰����Trim �ķ�ʽ���м��еĲ��ԡ� 
template <typename T> class book {
};

MLogFile logger;
using namespace std;


char mbr[512];
TEST(endian , size)
{
	EXPECT_EQ( sizeof(mbr), 512 );
	EXPECT_EQ( sizeof(int), 4 );
	EXPECT_EQ( sizeof(long), 4 );
	EXPECT_EQ( sizeof(long long ), 8 );
}

TEST(trim_pod, string)
{
	EXPECT_EQ((1-1) ,0);
	
	string test("\t\t test test  bbbbbbbbbbbb \t\t\t\n\n\n");
	char tmp[256]= "\t\t test test|\t \t\n ";
	char tmp1[256]= "1234567             \n\n\n\n\n\t\t\t\t\t";
	char tmp2[256]= "\t\t\t\t\t\t\t\t\t\t\t\n\n\n\n\n\n\n1234567";
	//10���ո� sizeof() =17
	char tmp3[256]= "1234          567";

	MString::Trim(tmp);
	EXPECT_EQ(MString(tmp), MString("test test|"));
	
	MString::Trim(tmp1);
	EXPECT_EQ(strlen(tmp1), 7);
	EXPECT_EQ(MString(tmp1), MString("1234567"));
	
	MString::Trim(tmp2);
	EXPECT_EQ(strlen(tmp2), 7);
	EXPECT_EQ(MString(tmp2), MString("1234567"));

	MString::Trim(tmp3);
	EXPECT_EQ(strlen(tmp3), 17);
}

TEST(trim_stl_string, string)
{
	//sizeof() 10�ո�+8
	string tmp("          12345678");
	MString::Trim((char*) tmp.c_str());
	EXPECT_NE(tmp.size(), 8);
	EXPECT_EQ(strlen(tmp.c_str()), 8);
	EXPECT_NE(tmp.length(), 8);

	//Trim ���Զ��ڴ����ݽ����޸ģ� ���ǲ��ܸı䣬 string ����ĳ��ȵ����ݣ� ֻ��ͨ�� string trimString(orgin.c_str()) �ķ�ʽ���¹���һ���µ�string. 
	string tmp2("          12345678\t\t\t\t\t\t\t\t\n\n\n\n\n\n\n\n");
	MString::Trim((char*) tmp2.c_str());
	EXPECT_NE(tmp2.size(), 8);
	EXPECT_EQ(strlen(tmp2.c_str()), 8);
	EXPECT_NE(tmp2.length(), 8);
	
	string tmp4(tmp2);
	EXPECT_NE(tmp4.length(), 8);
	
	string tmp5(tmp2.c_str());
	EXPECT_EQ(tmp5.length(), 8);
	EXPECT_EQ(tmp5, string("12345678"));


}
int main(int argc, char * argv[])
{
	logger.Instance(MString(argv[0])+".log", 1000);
	logger.WriteError("test", "test");
	testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}

