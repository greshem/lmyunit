//ODE_Treanor.cpp	 积分一步特雷纳法
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

#include <iostream>							//输入输出流头文件
//#include "OrdinaryDifferentialEguation.h"	///求解常微分方程(组)头文件
using namespace std;						//名字空间

int main(void)
{	
	double y[3] = {1.0, 0.0, -1.0}, t(0.0), h(0.001);
	valarray<double> vy(y, 3);
	
  	cout.setf(ios::fixed);	//输出数据为定点法
	cout.precision(6);		//精度6位
	int i, j;

	cout << "t = " << t << endl;

	for(int j=0; j<3; j++)
		cout << "    y(" << j << ") = " << y[j] << "\t";
	cout << endl;

	for(int i=0; i<10; i++)
	{
		ODE_Treanor(t,h,vy);
		t = t + h;
		cout << "t = " << t << endl;
		for(j=0; j<3; j++)
			cout << "    y(" << j << ") = " << vy[j] << "\t";
		cout << endl;
    }
	cout << endl;
}

//计算微分方程组中各方程右端函数值
template <class _Ty>
void FunctionValueT(_Ty t, valarray<_Ty>& y, valarray<_Ty>& d)
{
	int n = y.size();	//微分方程组中方程的个数，也是未知函数的个数

    d[0]=-21.0*y[0]+19.0*y[1]-20.0*y[2];
    d[1]=19.0*y[0]-21.0*y[1]+20.0*y[2];
    d[2]=40.0*y[0]-40.0*y[1]-40.0*y[2];
}

