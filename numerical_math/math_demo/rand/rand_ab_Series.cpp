//rand_ab_Series.cpp	产生任意[a,b]区间内均匀分布伪随机整数序列
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
	size_t a = 1000, b = 9999,  stCount=40;
	valarray<size_t> rip(40);
	size_t seed = time (NULL);					//取种子
	
	rand_ab_Series(a, b, seed, rip, stCount);	//生成随机数

	ValarrayPrint(rip);							//输出至显示器

	cout << endl;
}

