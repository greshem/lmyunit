#!/usr/bin/perl
#2011_06_30_ ������ add by greshem

if( -d  "unitcode")
{
	print "lmyunit û�д��, �ֽڱ��� copy��װ\n";
	chdir("unitcode");
	system("nmake /f makefile.vc");
	chdir("../");
	if( ! -f  "unitcode\\unitcode.lib")
	{
		die("�������,�������ĳ�ͻ������\n");
	}
	else
	{
		system("copy unitcode\\unitcode.lib d:\\usr\\lib\\ ");
	}
	if( -f "d:\\usr\\lib\\unitcode.lib")
	{
		print "lmyunit ��װ�ɹ�\n";
	}

	mkdir("d:\\usr\\include\\lmyunit\\");
	system("xcopy /y /S unitcode  d:\\usr\\include\\lmyunit\\unitcode");
	system("copy unitlib.h   d:\\usr\\include\\lmyunit\\");
}
