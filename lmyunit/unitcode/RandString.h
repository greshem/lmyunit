#ifndef __RAND_STRING__
#define  __RAND_STRING__
//qzj 20100629, ��֮ǰ����ɢ�� randstring ���� ����һ�� . 

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string> 
#include <vector> 
#include <iostream> 
#include <algorithm>
#include <iterator> 
using namespace std;
  
string RandString (int strLen);

 void  rand_mem_with_ascii (char *input, int strLen);

string RandPath(int number);

 string RandFilePath (int number);

vector<string> RandVecString (int strLen, int size);

char  * stringFromFile (char *fileName);

#endif


