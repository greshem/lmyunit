#include <unitcode/RandString.h>
#include <gtest/gtest.h>
//###################################################

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

extern "C" int main_gtest(int argc, char * argv[])
{
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

int main(int argc, char *argv[])
{

    string a= RandPath(1); //target call
	printf("%s\n", a.c_str());

	//main_gtest(argc, argv);
    return 0;
}
