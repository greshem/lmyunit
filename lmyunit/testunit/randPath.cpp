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
//2010_06_29 by qzj. 
//#2010_08_11_10:22:27 add by qzj
using namespace std;
int main(int argc, char *argv[])
{
	MString str("cc.cpp");
	cout<<str.c_str()<<endl;
	cout<<"cc.cpp"<<endl;
	for(int i=0;i<=100;i++)
	{
	//cout <<RandPath(random()%6+1)<<endl;
	cout <<RandFilePath(rand()%6+1)<<endl;
	}
//	vector<string> vecStr=RandVecString(10, 100);
//	copy(vecStr.begin(), vecStr.end(), ostream_iterator<string>(cout, "\n"));
	return 0;
}
