//###################################################
#include <fstream>
//#include <dirent.h>
#include <string> 
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unitlib.h>
//#include <QzjUnit.hpp>
//#include <MLmyUnit.hpp>
#include <map>
#include <iostream> 
#include <algorithm>
#include <vector> 
#include <iterator>  
#include <gtest/gtest.h>
TEST (init, MDateTIme)
{

	MDateTime date;
	date.SetCurDateTime();
	//cout<<date.DateToString()<<endl;
	ASSERT_GT(date.DateTimeToTimet(), 1);
	ASSERT_GT(date.DateToLong(), 1);
	ASSERT_GT(date.TimeToLong(), 1);
}
TEST ( decode, MDateTime)
{
	unsigned short year, month, day;
	MDateTime date(2008, 8, 8);
	date.DecodeDate(&year, &month, &day);
	ASSERT_EQ(year, 2008);
	ASSERT_EQ(month, 8);
	ASSERT_EQ(day, 8);

	unsigned short hour, min, sec;
	//A股开盘
	MDateTime time(9, 30, 0, 100);

	time.DecodeTime( &hour, &min, &sec);
	ASSERT_EQ(hour, 9);
	ASSERT_EQ(min, 30);
	ASSERT_EQ(sec, 0);	
			
}

TEST (getDayofWeek, MDateTime)
{
	//星期三
	MDateTime date(2010, 8, 11);
	ASSERT_EQ(date.GetDayOfWork(), 3);	
	ASSERT_EQ(MString("2010-08-10"), MString("2010-08-10"));	
	ASSERT_EQ(MString("2010-8-11"), date.DateToString());
	ASSERT_NE(MString("2010-08-11"), date.DateToString());
	//建国日期 , 星期六
	MDateTime nationDay(1949, 10, 1);
	//这里错误。 
	ASSERT_LT(nationDay.GetDayOfWork(), 6);
	ASSERT_EQ(nationDay.GetDayOfWork(), 6);
}
int main(int argc, char * argv[])
{
	//print
	testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
	
	//printFSInfo("/dev/sdb1") ;
}

