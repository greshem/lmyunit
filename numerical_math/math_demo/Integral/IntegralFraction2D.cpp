//IntegralFraction2D.cpp 二重连分式法求积
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

#include <iostream>		//输入输出流头文件
//#include "Integral.h"	//积分头文件
using namespace std;	//名字空间

int main(void)
{
	long double eps(0.00005), a(0), b(1);

	long double dValue = IntegralFraction2D(a, b, eps);
                
	cout << "IntegralSimpson1D()" << endl << endl;

	cout << "dValue = " << dValue << endl << endl;
}

//计算上、下限y1(x)与y0(x)
template <class _Ty>
void FunctionBoundaryF2D(_Ty x, valarray<_Ty>& y)
{
	y[1] = sqrt(1.0 - x * x);
	y[0] = - y[1];
}

//计算被积函数f(x,y)值
template <class _Ty>
_Ty FunctionValueF2D(_Ty x, _Ty y)
{
	_Ty dValue;

	dValue = exp(x * x + y * y);

    return(dValue);
}

