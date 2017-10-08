//IntegralSimpson2D.cpp		 二重变步长辛卜生法求积
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

#include <iostream>			//输入输出流头文件
//#include "Integral.h"		//积分头文件
using namespace std;		//名字空间

int main(void)
{	
	double eps = FLOATERROR, a(0), b(1);
	                
	cout << "IntegralSimpson2D()" << endl << endl;
    
	double dValue = IntegralSimpson2D(a,b,eps);

	cout << "dValue = " << dValue << endl << endl;
}

// 计算上、下限y1(x)、y0(x)值
template <class _Ty>
void FunctionBoundaryIS2D(_Ty x, valarray<_Ty>& y)
{
	y[0] = -sqrt(1.0 -x *x);
    y[1] = -y[0];
}

// 计算被积f(x,y)函数值
template <class _Ty>
_Ty FunctionValueIS2D(_Ty x, _Ty y)
{
	_Ty zValue;

	zValue = exp(x * x + y * y);
    
	return(zValue);
}



