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
//��� null_2_space_v3.cpp ʹ�ã� ����ͨ��VIM �ı��ķ�ʽ�鿴��־�ˡ� 
using namespace std;
int main(int argc, char *argv[])
{
	FILE *log;
	char tmp[1024];
	//MString tmp;
	if(argc != 2)
	{
		die("Usage: %s file.log", argv[0]);
	}
	log= fopen(argv[0], "r");
	if(log ==NULL)
	{
		die("open file error %s", "bb.log");
	}
	while(fgets(tmp, sizeof(tmp), log))
	{
		MString::TrimLeft(tmp);
		MString::TrimRight(tmp); 
		cout<<tmp<<endl;
	}
	return 1;
}
