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
//2010_09_02 by greshem. 

TEST(md5, checkcode)
{
	MMD5 md5;
	EXPECT_EQ(md5.MD5("123456", 6), "e10adc3949ba59abbe56e057f20f883e");
	EXPECT_EQ(md5.MD5("654321", 6), "c33367701511b4f6020ec61ded352059");
	EXPECT_NE(md5.MD5("richet", 6), "ddfd");
}


TEST(endian , size)
{
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


