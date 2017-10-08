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

//2010_06_30 by qzj. 
//#2010_08_12_14:37:14 add by qzj
using namespace std;
int main(int argc, char *argv[])
{
	if( argc != 2)
	{
		die(" Usage: %s  string ", argv[0]);
	}
	die("%s", argv[1]);
	return 0;
}
