//###################################################
#include <fstream>
#include <dirent.h>
#include <string> 
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unitlib.h>
//#include <QzjUnit.hpp>
//#include <MLmyUnit.hpp>
#include <map>
#include <iostream> 
#include <algorithm>
#include <vector> 
#include <iterator>  
using namespace std;
int main()
{
	MDateTime date;
	date.SetCurDateTime();
	//cout<<date.DateToString()<<endl;
	printf("%s\n", date.DateToString().c_str());
	return 0;
}
