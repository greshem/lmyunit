#include <unitlib.h>
#include <algorithm>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <iostream> 
#include <iterator>  
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string> 
#include <vector> 


char mbr[512];
using namespace std;
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
TEST(gen_ini_reload, inifile)
{
	unlink("output.ini");
	string ini;
	ini+="[sect1]\n";
	ini+="	key=44\n";
	ini+="	key2=44\n";
	ini+="	key3=44\n";

	ini+="[sect2]\n";
	ini+="	key=44\n";
	ini+="	key2=44\n";
	ini+="	key3=44\n";

	ini+="[sect3]\n";
	ini+="	key=44\n";
	ini+="	key2=44\n";
	ini+="	key3=44\n";

	ini+="[sect4]\n";
	ini+="	key=44\n";
	ini+="	key2=44\n";
	ini+="	key3=44\n";

	file_put_content("output.ini", ini, 0);
	EXPECT_EQ(ini.size(), filesize("output.ini"));

	IniFile  IniFile("output.ini", 1);
	EXPECT_EQ(IniFile.get<int>("sect1", "key"), 44);
	EXPECT_EQ(IniFile.get<int>("sect2", "key"), 44);
	EXPECT_EQ(IniFile.get<int>("sect3", "key"), 44);

	EXPECT_EQ(IniFile.get<string>("sect1", "key"), "44");
	EXPECT_EQ(IniFile.get<string>("sect2", "key"), "44");
	EXPECT_EQ(IniFile.get<string>("sect3", "key"), "44");

	EXPECT_EQ(IniFile.get<int>("sect1", "key2"), 44);
	EXPECT_EQ(IniFile.get<int>("sect2", "key2"), 44);
	EXPECT_EQ(IniFile.get<int>("sect3", "key2"), 44);

	EXPECT_EQ(IniFile.get<int>("sect1", "key3"), 44);
	EXPECT_EQ(IniFile.get<int>("sect2", "key3"), 44);
	EXPECT_EQ(IniFile.get<int>("sect3", "key3"), 44);
}
TEST(set_in_memory , inifile)
{
	IniFile   ini("petty.ini", 1);
	//IniFile<char>   ini("petty.ini", 0);

    //fstream  file("
    ini.set<int>("sect1", "key", 44);
    ini.set<short>("sect2", "key", 44);
    ini.set<float>("sect3", "key", 44);
    ini.set<string>("sect4", "key", "44");
	EXPECT_EQ(	ini.get<int>("sect1", "key") , 44);
	EXPECT_EQ(	ini.get<short>("sect2", "key") , 44);
	EXPECT_EQ(	ini.get<string>("sect4", "key") , "44");

	//ini.Dump();
	ini.save("test2.ini", 1);
	EXPECT_EQ(MFile::IsExist("test2.ini"), 1);
	
}
int main(int argc, char * argv[])
{
	testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}


