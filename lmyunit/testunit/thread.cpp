#include <stdlib.h>
#include  <unitlib.h>
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
//2010_06_30 by qzj. 
using namespace std;
static 
void * __stdcall work( void *in)
{

	int i;
	i=*(int *)in;
	//while( 1)
	for(int i=0;i<=1;i++)

	{
		printf("thread  %d\n", i);
		//i++;
#ifdef WINDOWSCODE
		Sleep(1000);
#else
		//usleep(10);
		sleep(1);
#endif
	}
	return '\0';;
}
int main(int argc, char *argv[])
{
	MThread thread;
	MThread thread1;
	int a=10;
	int b=1000;
	thread.StartThread("test1", work, &a);
	thread1.StartThread("test2", work, &b);
	for(int i=0;i<=1;i++)
	{
#ifdef WINDOWSCODE
		Sleep(1000);
#else
		//usleep(1);
		sleep(1);
		printf("parent%d\n", i);
#endif
	}
	return 0;
}
