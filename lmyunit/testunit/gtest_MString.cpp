//###################################################
//ASSERT_EQ 	EXPECT_EQ 	相等
//ASSERT_NE 	EXPECT_NE 	不等
//ASSERT_GT 	EXPECT_GT 	大于
//ASSERT_LT 	EXPECT_LT 	小于
//ASSERT_GE 	EXPECT_GE 	大于或等于
//ASSERT_LE 	EXPECT_LE 	小于或等于
//ASSERT_TRUE 	EXPECT_TRUE 	判真
//ASSERT_FALSE 	EXPECT_FALSE 	判假
//ASSERT_FLOAT_EQ 	EXPECT_FLOAT_EQ 	单精度浮点值相等
//ASSERT_DOUBLE_EQ 	EXPECT_DOUBLE_EQ 	双精度浮点值相等
//ASSERT_NEAR 	EXPECT_NEAR 	浮点值接近
//ASSERT_STREQ 	EXPECT_STREQ 	C字符串相等
//ASSERT_STRNE 	EXPECT_STRNE 	C字符串不等
//ASSERT_STRCASEEQ 	EXPECT_STRCASEEQ 	C字符串相等（忽略大小写）
//ASSERT_STRCASENE 	EXPECT_STRCASENE 	C字符串不等（忽略大小写）
#include <fstream>
////#include <dirent.h>
#include <string> 
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#include <QzjUnit.hpp>
//#include <MLmyUnit.hpp>
#include <unitlib.h>
#include <map>
#include <iostream> 
#include <algorithm>
#include <vector> 
#include <iterator>  
#include <gtest/gtest.h>
//#include "MString_template.hpp"
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
TEST(equal, MString)
{
	
	EXPECT_EQ(MString("qianzhongjie")==MString("qianzhongjie"), true );
	EXPECT_EQ(MString("qianzhongjie")!=MString("qianzhongji33"), true );
	EXPECT_NE(MString("qianzhongjie"), MString("qianzhongji33") );
	//EXPECT_EQ(MString("qianzhongjie"), MString::Trim(("   qianzhongjie      "))  );
}
TEST(trim, MString)
{
	MString qianzhongjie("  qianzhongjie  ");
	MString qianzhongjie2("       qianzhongjie       ");  
	qianzhongjie.Trim();
	qianzhongjie2.Trim();

	EXPECT_EQ(	qianzhongjie , qianzhongjie2  );
	EXPECT_EQ(	qianzhongjie.Length() , qianzhongjie2.Length()  );
	EXPECT_EQ(	qianzhongjie.Length() , sizeof("qianzhogjie")  );

}
TEST (Upper, MString)
{
	
	MString a("qianzhongjie");
	a.Upper();
	ASSERT_EQ(a[0], 'Q');	
	ASSERT_EQ(a[1], 'I');	
	a.Lower();

	ASSERT_EQ(a[0], 'q');	
	ASSERT_EQ(a[1], 'i');	
}

TEST (SetAt , MString)
{
	MString  a("qianzhonvjie");
	a.SetAt(0, 'w');
	a.SetAt(1, 'w');
	a.SetAt(2, 'w');
	a.SetAt(3, 'w');
	EXPECT_EQ(a[0], 'w');
	EXPECT_EQ(a[1], 'w');
	EXPECT_EQ(a[2], 'w');
	EXPECT_EQ(a[3], 'w');
}

TEST (FormatString ,MString)
{
	MString  a;
	EXPECT_EQ(a.Length(), 0);
	
	a.FormatString("%d", 1);
	EXPECT_EQ(a.Length(), 1);
	EXPECT_EQ(a, "1");
	
	a.FormatString("%d", 111);
	EXPECT_EQ(a.Length(), 3);
	EXPECT_EQ(a, "111");
}

TEST (StringPosition, MSring)
{
	MString neddle("neddle");;
	MString haystack("haystack has a neddle");
	ASSERT_GT( haystack.StringPosition(neddle), 0);
	EXPECT_NE(	 haystack.StringPosition(neddle), 0);

}
TEST ( Template , MString)
{
	MString a("richtech");
	MString b("richtech");
	MString c("richtech");
	ASSERT_EQ(a.Length(), 8);	
	ASSERT_EQ(b.Length(), 8);	
	ASSERT_EQ(c.Length(), 8);	
}

TEST(add , MString)
{
	MString rich("richtech");
	const char *a="chinese";
	MString tmp=a+rich;	
	ASSERT_EQ(tmp.Length(), 15);
	MString tmp2=tmp+rich;
	ASSERT_EQ(tmp2.Length(), 15+8);
}
TEST(instance, MString)
{
	MString a('a');
	ASSERT_EQ(a.Length(), 1);

	MString b('a', 10);
	ASSERT_EQ(b.Length(), 10);
	
	short num=10000;	
	MString c(num);
	ASSERT_EQ(c.Length(), 5);
	
	int num2=1000000000;
	MString d(num2);
	ASSERT_EQ(d.Length(), 10);

	MString e(d);
	ASSERT_EQ(e.Length(), 10);
	ASSERT_EQ(e, d);
}

TEST(c_str, MString)
{
	const char *rich="richtech";
	MString a(rich);
	a+=rich;
	EXPECT_EQ (a.Length(), 8*2);

	a+=rich;
	EXPECT_EQ (a.Length(), 8*3);
	a+=rich;
	EXPECT_EQ (a.Length(), 8*4);
	a+=rich;
	EXPECT_EQ (a.Length(), 8*5);

	a+=rich;
	EXPECT_EQ (a.Length(), 8*6);
	a+=rich;
	EXPECT_EQ (a.Length(), 8*7);
	a+=rich;
	EXPECT_EQ (a.Length(), 8*8);

	a+=rich;
	EXPECT_EQ (a.Length(), 8*9);
	a+=rich;
	EXPECT_EQ (a.Length(), 8*10);
	a+=rich;
	EXPECT_EQ (a.Length(), 8*11);
	
	cout<<a.c_str()<<endl;
}
int main(int argc, char * argv[])
{
	//print
	testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
	
	//printFSInfo("/dev/sdb1") ;
}

