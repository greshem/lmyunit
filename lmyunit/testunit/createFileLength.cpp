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
#include <gtest/gtest.h>
//2010_09_10 by greshem. 
MLogFile logger;
using namespace std;
int main(int argc, char *argv[])
{
	
	if(argc != 2)
	{
		die("Usage: %s length \n", argv[0]);
	}
	
	unsigned	int length=atoi( argv[1]);

	MString filename;
	filename.FormatString("%d", length);
	filename+=".nothing";

	MFile output;
	output.Create(filename);	

	//一行带上换行符有1024个字节。 
	int line_len=132;
	int line_count=length/line_len;
	
	MString fill;
	int i=0;
	for(i=0; i<line_count; i++)
	{
		fill.FormatString("%d", i);
		MString  tmp( fill.c_str(), line_len-1);
		tmp+="\n";
		output.Write(tmp.c_str(), line_len);		
	}

	//尾行填充
	if( (length%line_len) !=0)
	{
		fill.FormatString("%d", i);
		MString last(fill.c_str(), length%line_len-1);
		last+="\n";
		output.Write(last.c_str(), length%line_len);
	}
	output.Close();
	//assert(length== filesize(filename.c_str()));
	return 0;
}
