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
//2010_07_15 by qzj. 
//#2010_08_11_10:18:44 add by qzj
//之前没有模板限制啊添加.
MLogFile logger;
TEST(AAAAAAAAAAA ,BBBBBBBBBBBB)
{
	MString tmp("wenwen");
	
	EXPECT_EQ(MString("wenwen"), MString("wenwen"));
	EXPECT_EQ(MString("wenwen2"), "wenwen2" );
	EXPECT_EQ(tmp, MString("wenwen") );
	tmp.Upper();
	EXPECT_TRUE((tmp=="WENWEN"));
};
TEST(CCCCCCCCCCCC ,BBBBBBBBBBBB)
{
	EXPECT_EQ(MString("wenwen"), MString("wenwen"));
	EXPECT_EQ(MString("wenwen2"), "wenwen2" );
}
TEST(QIAN3 ,BBBBBBBBBBBB)
{
	EXPECT_EQ(MString("wenwen"), MString("wenwen"));
	EXPECT_EQ(MString("wenwen2"), "wenwen2" );
}

TEST(QIAN4 ,BBBBBBBBBBBB)
{
	EXPECT_EQ(MString("wenwen"), MString("wenwen"));
	EXPECT_EQ(MString("wenwen2"), "wenwen2" );
}
using namespace std;
int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();	
	return 0;
}
