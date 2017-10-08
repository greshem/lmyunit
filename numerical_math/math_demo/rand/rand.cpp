// rand.cpp		C++提供的rand()函数
#include <fstream>
#include <dirent.h>
#include <string> 
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <map>
#include <iostream> 
#include <algorithm>
#include <vector> 
#include <iterator>  
#include <numerical_math.hpp>
// 该程序利用time与srand函数作为随机数生成器的种子，生成10个随机整数，然后输出。

//#include <random.h>		//随机算法头文件
#include <iostream>		//输入输出流头文件			
#include <time.h>		//时间头文件
using namespace std;	//名字空间

int main( void )
{
    // 随机数生成器需要的种子值使用当前时间，以便每次程序运行时该种子值都不相同。
	srand( (size_t)time( NULL ) );

    // 输出10个随机数
	for(size_t i = 0; i < 10; i++){
		cout.width(6);
		cout << rand() << endl;
		//ofs << rand() << endl;
	}
}

