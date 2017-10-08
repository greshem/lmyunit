//LinearRegression1D.cpp	一元线性回归分析
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

#include <iostream>			//模板类输入输出流iostream标准头文件
#include <valarray>			//模板类valarray的标准头文件
//#include <Statistic.h>		//数据处理与回归分析头文件
using namespace std;		//名字空间

int main(void)
{	
	valarray<long double> a(2);
	valarray<long double> dt(6);
	long double x0(192), h(2);
	
	long double x[11] = 
	{
		0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0
	};
	
	long double y[11] = 
	{
		2.75,2.84,2.965,3.01,3.20,3.25,3.38,3.43,3.55,3.66,3.74
	};
	 
	valarray<long double> xx(x, 11);
	valarray<long double> yy(y, 11);

	//LinearRegression1D.cpp	一元线性回归分析
    LinearRegression1D(xx, yy, a, dt);

	cout << endl << "a = " << a[1] << "\t b = " << a[0] << endl;
	cout << endl << "q = " << dt[0] << "\t s = " << dt[1];
						cout <<  "\t p = " << dt[2] << endl;
	cout << endl << "umax = " << dt[3] << "\t umin = " << dt[4];
								cout <<  "\t u = " << dt[5] << endl;
}
