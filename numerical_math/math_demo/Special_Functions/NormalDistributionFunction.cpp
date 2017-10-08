//NormalDistributionFunction.cpp	
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
//正态分布函数

#include <iostream>					//模板类输入输出流标准头文件
//#include <SpecialFunction.h>		//数学变换头文件
using namespace std;				//名字空间

int main(void)
{	
	double x, y, b, c;
	double a[2]={ -1.0,3.0};
    double d[2]={ 0.5,15.0};

	
	for(int i=0; i<2; i++)
	{
		b=a[i]; 
		c=d[i]; 
		x=-10.0;
		for(int j=0; j<5; j++)
		{
			y = NormalDistributionFunction(b, c, x);
			cout << " NormalDistributionFunction(" << b << "," << c 
									<< "," << x << ")\t= " << y << endl;
			x = x + 5.0;
		}

	}
}


