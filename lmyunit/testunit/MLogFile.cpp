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
using namespace std;
int main(int argc, char *argv[])
{
	MString str("MLogFile.cpp");
	cout<<str.c_str()<<endl;
	MLogFile logfile;
	logfile.Instance("aa.log", 10000);
	for(int i=0; i<=100; i++)
	{
		logfile.WriteError("����", "%s %d", " ��Ԫ������Ҫ�� ", i);
	}
	logfile.Close();
	cout<<" aa.log ��־���ɣ� ����Խ�ȥ�鿴"<<endl;
	return 0;
}
