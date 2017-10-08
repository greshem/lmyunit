//ODE_MersonVariationalStep.cpp	
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
//变步长积分默森法

#include <iostream>							//输入输出流头文件
//#include "OrdinaryDifferentialEguation.h"	//求解常微分方程(组)头文件
using namespace std;						//名字空间

int main(void)
{	
	double y[2] = {0.0, 1.0}, t(0.0), h(0.1), eps(FLOATERROR);
	valarray<double> vy(y, 2);
	matrix<double> vz(2,11);
	
  	cout.setf(ios::fixed);	//输出数据为定点法
	cout.precision(6);		//精度6位

	ODE_MersonVariationalStep(t,h,2,vy,eps,11,vz);

	for(int i=0; i<11; i++)
	{
		double x = h * i;
		cout << "t = " << x << endl;
		cout << "    y(0) = " << vz(0, i) << "\t   y(1) = " << vz(1, i) << endl;
    }
}

//计算微分方程组中各方程右端函数值
template <class _Ty>
void FunctionValueMVS(_Ty t, valarray<_Ty>& y, valarray<_Ty>& d)
{
	_Ty q;

	int n = y.size();	//微分方程组中方程的个数，也是未知函数的个数

    q = 60.0 * (0.06 + t* (t - 0.6));
    d[0] = q * y[1];
	d[1] = -q * y[0];
}

