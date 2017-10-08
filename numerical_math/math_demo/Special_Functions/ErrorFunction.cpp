//ErrorFunction.cpp				
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
//误差函数

#include <iostream>				//模板类输入输出流标准头文件
////#include <SpecialFunction.h>	//数学变换头文件
using namespace std;			//名字空间

int main(void)
{	
	double x, y;
	
	for(int i=1; i<20; i++)
	{
		for(int j=0; j<2; j++)
		{
			x = 0.05 * (2.0 * i +j);
			y = ErrorFunction(x);
			cout << "    ErrorFunction(" << x << ")\t=" << y;
		}
		cout << endl;
	}
	
	x = 2.0;
	y = ErrorFunction(x);
	cout << "    ErrorFunction(" << x << ")\t=" << y << endl;
}

