#!/usr/bin/perl
#2011_06_30_ 星期四 add by greshem

if( -d  "unitcode")
{
	print "lmyunit 没有打包, 字节编译 copy安装\n";
	chdir("unitcode");
	system("nmake /f makefile.vc");
	chdir("../");
	if( ! -f  "unitcode\\unitcode.lib")
	{
		die("编译出错,解决编译的冲突的问题\n");
	}
	else
	{
		system("copy unitcode\\unitcode.lib d:\\usr\\lib\\ ");
	}
	if( -f "d:\\usr\\lib\\unitcode.lib")
	{
		print "lmyunit 安装成功\n";
	}

	mkdir("d:\\usr\\include\\lmyunit\\");
	system("xcopy /y /S unitcode  d:\\usr\\include\\lmyunit\\unitcode");
	system("copy unitlib.h   d:\\usr\\include\\lmyunit\\");
}
