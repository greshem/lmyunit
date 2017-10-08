#include <stdlib.h>
//#include <unitlib.h>
//#include <QzjUnit.hpp>
#include <unitlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string> 
#include <dirent.h>
#include <fstream>
#include <iterator>  
#include <vector> 
#include <algorithm>
#include <iostream> 
#include <map>
#include <gtest/gtest.h>
//2011_03_30 by greshem. 


MLogFile logger;
using namespace std;
int main(int argc, char *argv[])
{
	if(argc != 2)
    {
        printf("Usage: %s file_list \n", argv[0]);
    //    exit(-1);
    }
    printf("%s\n", "dump_vec_string.cpp");

	logger.Instance(MString(argv[0])+".log", 1000);
	logger.WriteError("test", "test");

	MString str("dump_vec_string.cpp");
	cout<<str.c_str()<<endl;

	vector<string> vec_str;
	vec_str.push_back("test");
	vec_str.push_back("test2");
	vec_str.push_back("test3");
	vec_str.push_back("test4");
	vec_str.push_back("test5");

	//dump(vec_str);
	return 0;
}
