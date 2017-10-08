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
using namespace std;
int WriteLongString(MFile &in , int writeLength);
int main(int argc, char *argv[])
{
	MString str("MFile.cpp");
	MFile file;
	for(int i=0; i<=100;i++)
	{
		MString fileName(RandFilePath(6).c_str());	
		cout<<"deal with file "<<fileName<<endl;
		MFile::CreateDirectoryTree(fileName.basename());
		file.Create(fileName);
		WriteLongString(file, 10240);
		file.Close();
	
	}
	file.Close();
	cout<<str.c_str()<<endl;
	cout<<"MFile.cpp"<<endl;
	return 0;
}

int WriteLongString(MFile &in , int writeLength)
{
	int i=0;
	const	int screenWidth=80;
	while(i<writeLength)
	{
		in.WriteString(RandString(screenWidth -1 ).c_str());
		i+=screenWidth;
	}
	return 0;
}
