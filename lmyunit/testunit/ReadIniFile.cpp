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
//2010_08_28 by greshem. 

template <typename T> class book {
};

int touch_file(char *path);

MLogFile logger;
using namespace std;
int main(int argc, char *argv[])
{
	logger.Instance(MString(argv[0])+".log", 1000);
	logger.WriteError("test", "test");

	touch_file("output.ini");

	IniFile  petty("output.ini");
	cout<< petty.get<string>("sect1", "key");
	return 0;
}

int touch_file(char *path)
{
	FILE *fp=fopen(path, "a+");
	if(fp==NULL)
	{
		return -1;
	}
	fclose(fp);
	return 1;
}
