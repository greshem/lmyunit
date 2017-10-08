//ExtremumFraction1D.cpp 一维极值连分式法
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
	valarray<int> js(2);
	valarray<long double> x(2);
	long double eps = LONGDOUBLEERROR;
	
	x[0]=1;
    
	ExtremumFraction1D(x, eps, 10, js);
	
	cout << "js[0] = " << js[0] << endl;
	if (js[1] < 0)
		cout << "MIN:  ";
    else
		cout << "MAX:  ";
	cout << "x = " << x[0] << "\t" << "f(x) = " << x[1] << endl;
}

//*	计算函数及导数值
template <class _Ty> 
void FunctionValueEF1D(_Ty x, valarray<_Ty>& y)
{
	y[0] = (x-1.0) * (10.0-x);	//计算f(x)函数值
    y[1] = -2.0 * x + 11.0;		//计算f(x)导数值
}


