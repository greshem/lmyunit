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
#include <stdarg.h>
using namespace std;
//void die(char *format, ...);
int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		die("Usage: %s file_in file_out\n", argv[0]);	
	}
	int chr;
	FILE *in;
	FILE *out;
	in=fopen(argv[1],"r");
	if(in ==NULL)
	{
		die("open file error");
	}
	out=fopen(argv[2], "w");
	if(out==NULL)
	{
		die("create file error");
	}
	while((chr=fgetc(in)) != EOF)
	{
		if(chr=='\0')
		{
			chr=' ';
		}
		fputc(chr, out);
	}
	return 1;
}
void Usage()
{
	cout<<"Usage: self filein fileout"<<endl;
	exit(-1);
}	
/*
void die(char *format, ...)
{
	static char tmp[1024];
	memset(tmp, '\0', sizeof(tmp));
	va_list(marker);
	va_start(marker, format);
	vsprintf(tmp, format, marker);
	va_end(marker);
	printf("%s\n", tmp);
	exit(-1);
}
*/
