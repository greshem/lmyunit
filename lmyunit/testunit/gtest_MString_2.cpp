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
//#2010_08_12_14:02:11 add by qzj<F6>
MLogFile logger;
TEST(AAAAAAAAAAA ,MString)
{
	MString tmp("wenwen");
	EXPECT_EQ(MString("wenwen"), MString("wenwen"));
	EXPECT_EQ(MString("wenwen2"), "wenwen2" );
	EXPECT_EQ(tmp, MString("wenwen") );
	tmp.Upper();
	EXPECT_TRUE((tmp=="WENWEN"));
};
TEST(CCCCCCCCCCCC ,MString )
{
	EXPECT_EQ(MString("wenwen"), MString("wenwen"));
	EXPECT_EQ(MString("wenwen2"), "wenwen2" );
}
TEST(QIAN3 ,MString)
{
	EXPECT_EQ(MString("wenwen"), MString("wenwen"));
	EXPECT_EQ(MString("wenwen2"), "wenwen2" );
}

TEST(QIAN4 ,MString)
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
