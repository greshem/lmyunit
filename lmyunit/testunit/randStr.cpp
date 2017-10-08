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
//2010_06_29 by qzj. 
//#2010_08_11_10:23:15 add by qzj
using namespace std;
int main(int argc, char *argv[])
{
	MString str("cc.cpp");
	cout<<str.c_str()<<endl;
	cout<<"cc.cpp"<<endl;
	//for(int i=0;i<=100;i++)
	//{
	//cout <<RandString(random()%20+1)<<endl;
	//}
	vector<string> vecStr=RandVecString(10, 100);
	copy(vecStr.begin(), vecStr.end(), ostream_iterator<string>(cout, "\n"));
	return 0;
}
