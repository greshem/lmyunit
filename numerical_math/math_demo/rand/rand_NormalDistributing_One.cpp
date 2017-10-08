//rand_NormalDistributing_One.cpp	产生任意均值与方差的一个正态分布随机数
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

int main(void)
{	
	double mu = 1.0, ro = 1.5;
	double seed = (double)time(NULL);	//取种子
	
	//ofstream ofs("3_6.dat");			//创建文件3_6.dat

	cout.setf(ios::fixed|ios::left);	//输出数据为定点法，靠左对齐
	cout.precision(6);					//精度6位

	for(size_t st = 0; st < 40; st++)
	{
		if (st % 5 == 0) cout << endl;
		cout << rand_NormalDistributing_One(mu, ro, seed) << "\t " ;
	}
	cout << endl;
}

