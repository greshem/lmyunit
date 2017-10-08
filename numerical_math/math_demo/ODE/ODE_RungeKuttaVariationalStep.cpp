//ODE_RungeKuttaVariationalStep.cpp		 
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
//变步长积分龙格-库塔法

#include <iostream>							//输入输出流头文件
//#include "OrdinaryDifferentialEguation.h"	//求解常微分方程(组)头文件
using namespace std;						//名字空间

int main(void)
{	
	double dy[2] = {0.0, 1.0}, t(0.0), h(0.1), eps(FLOATERROR);
	valarray<double> y(dy, 2);
		
  	cout.setf(ios::fixed);	//输出数据为定点法
	cout.precision(6);		//精度6位

	cout << " t = " << t << "\t y[0] = " << y[0] << "\t y[1] = " << y[1] << endl;

	for(int i=1; i<11; i++)
	{
		ODE_RungeKuttaVariationalStep(t,h,y,eps);
		t = t + h;
		cout << " t = " << t << "\t y[0] = " << y[0] << "\t y[1] = " << y[1] << endl;
	}
}

//计算微分方程组中各方程右端函数值
template <class _Ty>
void FunctionValueRKVS(_Ty t, valarray<_Ty>& y, valarray<_Ty>& d)
{
	int n = y.size();	//微分方程组中方程的个数，也是未知函数的个数

    d[0] = y[1];
	d[1] = -y[0]; 
}
