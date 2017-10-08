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
//2010_08_24 by qzj. 

template <typename T> class book {
};


char mbr[512];
TEST(endian , size)
{
	EXPECT_EQ( sizeof(mbr), 512 );
	EXPECT_EQ( sizeof(int), 4 );
	EXPECT_EQ( sizeof(long), 4 );
	EXPECT_EQ( sizeof(long long ), 8 );
}
TEST(filesize, Tools)
{
	if(MFile::IsExist("/etc/passwd"))
	{	
		EXPECT_GT(filesize("/etc/passwd"), 0);	
	}
}
TEST(file_put_content_11, Tools)
{
	string str("12345678");

	unlink(str.c_str());
	file_put_content(str, str,0);
	EXPECT_EQ(filesize(str), str.size());
	EXPECT_EQ(MFile::IsExist(str.c_str()) , 1);
	
	string cnt;
	file_get_content(str, cnt);
	cout<<cnt;
	EXPECT_EQ(str.size(), cnt.size());
}
TEST (shell_exec, Tools)
{
	string result;
	int ret=shell_exec("seq 1 2", result);
	EXPECT_EQ(result, "1\n2\n");
	ret=shell_exec("seq 1 3", result);
	EXPECT_EQ(result, "1\n2\n3\n");
}

TEST(str_replace, Tools)
{
	string logo("test__TEMPLATE__");
	string result=str_replace("__TEMPLATE__", "198308190917", logo);
	EXPECT_EQ(result, "test198308190917");
}

TEST(ucfirst, Tools)
{
	string logo("aa bb cc dd ee ff");
	string logo2("aa bb cc dd ee ff 11 22 33");

	string result=ucfirst(logo);
	EXPECT_EQ(result, "Aa Bb Cc Dd Ee Ff");

	result=ucfirst(logo2);
	EXPECT_EQ(result, "Aa Bb Cc Dd Ee Ff 11 22 33");

}

TEST(trim, Tools)
{
	string logo("	12345678\n\n\n\n\n\n");
	string result=trim(logo);
	EXPECT_EQ(result, "12345678");
}
int main(int argc, char * argv[])
{
	testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}

