//rand_ab_One.cpp	产生任意[a,b]区间内一个均匀分布伪随机整数
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

//#include <random.h>		//随机算法头文件
#include <iostream>		//输入输出流头文件			
#include <time.h>		//时间头文件
using namespace std;	//名字空间

//从[1000,9999]中产生40个随机整数
int main(void)
{		
	size_t a = 1000, b = 9999;
	size_t seed = time (NULL);				//取种子
	for(size_t st = 0; st < 40; st++)
	{
		if (st % 5 == 0) cout << endl;
		cout << rand_ab_One(a, b, seed) << "\t " ;
	}
	cout << endl;
}

