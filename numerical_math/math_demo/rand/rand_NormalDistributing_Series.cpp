//rand_NormalDistributing_Series.cpp 产生任意均值与方差的正态分布随机数序列
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

//产生40个均值与方差的正态分布随机数
int main(void)
{	
	double mu = 1.0, ro = 1.5;
	valarray<double> rip(40);
	size_t stCount=40;

	double seed = (double)time(NULL);	//取种子

	cout.setf(ios::fixed|ios::left);	//输出数据为定点法，靠左对齐
	cout.precision(6);					//精度6位
	
	//生成随机数
	rand_NormalDistributing_Series(mu, ro, seed, rip, stCount);	

	ValarrayPrint(rip);					//输出至显示器

	cout << endl;
}

