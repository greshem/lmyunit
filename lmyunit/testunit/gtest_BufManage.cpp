//#include <QzjUnit.hpp>
//#include <MLmyUnit.hpp>
#include <unitlib.h>
#include <gtest/gtest.h>
#include <fstream>
//#include <dirent.h>
#include <string> 
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <map>
#include <iostream> 
#include <algorithm>
#include <vector> 
#include <iterator>  
//20100927, 从刘勇那边修改过来. 
// 2011_03_30_19:30:08   星期三   add by greshem,
// 重新进行压力测试. 



MLogFile logger;
using namespace std;
//int main(int argc, char *argv[])
TEST(instance, BufferManger)
{
	//###############################################################################
	CBufManage  buffer(1024);
	int len=333;	
	int out;
	int i;
	//###############################################################################	
	//cout<<buffer.GetDataLen()<<endl;;
	EXPECT_EQ(buffer.GetDataLen(), 0);
	EXPECT_EQ(buffer.AddData((char *)&len, sizeof(int)) , sizeof(int));
	EXPECT_EQ(buffer.GetDataLen(), 4);

	memcpy(&out, buffer.GetBufPtr(), sizeof(int));	
	EXPECT_EQ(out, len);	
	memcpy(&out, buffer.GetBufPtr(), sizeof(int));	
	EXPECT_EQ(out, len);	

	//###############################################################################
	//0 1 2 3 4 5 6 7 9 10 11 12 13 14 15 16 ... 内存布局。 
	buffer.DelData(4, 0);
	EXPECT_EQ(buffer.GetDataLen(), 0);
	#define COUNT 1024
	for(int i=0; i<1024*COUNT; i++)
	{
		if((i%1024)==0)
			cout<<i<<endl;
		EXPECT_NE(buffer.AddData((char *)&i, sizeof(int)) , -1);
		EXPECT_EQ(buffer.GetDataLen(), (i+1)*4);
	}	

	for(int i=0; i<1024*COUNT; i++)
	{
		memcpy(&out, buffer.GetBufPtr()+4*i, sizeof(int));	
		EXPECT_EQ(out, i);	
	}


	//###############################################################################	
	//整个类对于内存的使用没有限制， 直到内存分配失败。 
	//EXPECT_EQ(buffer.AddData((char *)&i, sizeof(int)) , 1024*4+4);
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

