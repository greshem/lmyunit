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
//2010_07_16 by qzj. 
MLogFile logger;
using namespace std;
int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		die("%s file.txt", argv[0]);
	}
	string file(argv[1]);
	char *passwd=stringFromFile((char *)file.c_str());
	printf("%s", passwd);
	free(passwd);
	return 0;
}
