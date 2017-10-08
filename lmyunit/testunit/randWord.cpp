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
#include <stdlib.h>
//2010_07_06 by qzj. 
using namespace std;
int main(int argc, char *argv[])
{
	vector<string> vecStr=RandWord(100);
	copy(vecStr.begin(), vecStr.end(), ostream_iterator<string>(cout, "\n"));
	return 0;
}
