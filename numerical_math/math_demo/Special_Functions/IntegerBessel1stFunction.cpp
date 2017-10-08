//IntegerBessel1stFunction.cpp	
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
//第一类整数阶贝塞尔函数

#include <iostream>				//模板类输入输出流标准头文件
//#include <SpecialFunction.h>	//数学变换头文件
using namespace std;			//名字空间

int main(void)
{	
	double x, y;
	
	for(int n=0; n<6; n++)
	{
		x = 0.05;
		for(int j=1; j<5; j++)
		{
			y = IntegerBessel1stFunction(n, x);
			cout << "n = " << n << "  x = " << x 
					<< "\t  IntegerBessel1stFunction(n, x) = " << y << endl;
			x = x * 10.0;
		}
	}
}
