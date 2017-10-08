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

//2010_08_11 by qzj. 
MLogFile logger;
using namespace std;
int main(int argc, char *argv[])
{
	MString str("Inifile.cpp");
	int ret=logger.Instance(MString(argv[0])+".log", 1000);
	if(ret != 1)
	{
		die("ret =%d", ret);
	}
	logger.WriteError("test", "test");
	cout<<str.c_str()<<endl;
	cout<<"Inifile.cpp"<<endl;
	return 0;
}
