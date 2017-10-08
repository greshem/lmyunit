//ExtremumComplexND.cpp	n维极值复形调优法
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

#include <iostream>		//模板类iostream输入输出流标准头文件
//#include "Extremum.h"	//极值头文件

int main(void)
{	
	valarray<long double> x(3);
	valarray<long double> a(2);
	valarray<long double> b(2);
	matrix<long double> xx(3,4);
	long double eps = LONGDOUBLEERROR, alpha=1.3;

	x[0] = x[1] = 0;
    a[0] = a[1] = 0;
    b[0] = b[1] = 1.0e+35;

    int i = ExtremumComplexND(2,a,b,alpha,eps,x,xx,200);

	cout << "i = " << i << endl << endl;

	for (i=0; i<4; i++)
		cout << "x(0) = " << xx(0,i) << "\t x(1) = " << xx(1,i) 
									<< "\t f = " << xx(2,i) << endl;
	
	cout << endl;

    for (i=0; i<2; i++)
		cout << "x(" << i << ") = " << x[i] << endl;

	cout << endl;

    cout << "J = " << x[2] << endl;
}

//*	计算目标函数值
template <class _Ty> 
_Ty FunctionValueTarget(valarray<_Ty>& x, int n)
{
	_Ty y;
	
    y = -(9.0 - (x[0] - 3.0) * (x[0] - 3.0));
    y = y * x[1] * x[1] * x[1] / (27.0 * sqrt(3.0));

    return(y);
}

//*	计算函数约束条件的上、下限及条件值
template <class _Ty> 
void ConditionValue(int n, int m, valarray<_Ty>& x, valarray<_Ty>& c,
									valarray<_Ty>& d, valarray<_Ty>& w)
{

    c[0] = c[1] = 0.0;

    d[0] = x[0] / sqrt(3.0);
	d[1] = 6.0;

    w[0] = x[1];
	w[1] = x[0] + x[1] * sqrt(3.0);

	return;
}