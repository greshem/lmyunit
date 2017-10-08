#include <stdlib.h>
//#include <MLmyUnit.hpp>
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
//2010_06_29 by qzj. 
using namespace std;
int main(int argc, char *argv[])
{
	MString str("MFile.cpp");
	MFile file;
	file.Create("bbb.txt");
	for(int i=0; i<=100;i++)
	{
		MString tree(RandFilePath(6).c_str());	
		file.WriteString(tree);
		cout<<"---------------------"<<endl;
		cout<<tree.c_str()<<endl;
		cout<<tree.basename().c_str()<<endl;
		//MFile::CreateDirectoryTree(tree);
		//file.WriteString(RandFilePath(6).c_str());	
	}
	file.Close();
	cout<<str.c_str()<<endl;
	cout<<"MFile.cpp"<<endl;
	return 0;
}
