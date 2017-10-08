//IncompleteBetaFunction.cpp	
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
//不完全贝塔函数

#include <iostream>				//模板类输入输出流标准头文件
//#include <SpecialFunction.h>	//数学变换头文件
using namespace std;			//名字空间

int main(void)
{	
	double x(0.0), y, a0, b0;
	double a[5]={ 0.5,0.5,1.0,5.0,8.0};
    double b[5]={ 0.5,5.0,3.0,0.5,10.0};

	
	for(int i=0; i<6; i++)
	{
		cout << "x = " << x << endl;
		for(int j=0; j<5; j++)
		{
			a0 = a[j];
			b0 = b[j];
			y = IncompleteBetaFunction(a0, b0, x);
			cout << "\tIncompleteBetaFunction(" << a0 << "," << b0 
												<< ")\t= " << y << endl;
		}
		x = x + 0.2;
	}
}

