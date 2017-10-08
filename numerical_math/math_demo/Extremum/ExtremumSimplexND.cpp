//ExtremumSimplexND.cpp	n维极值单形调优法
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
	valarray<long double> f(3);
	matrix<long double> xx(2,3);
	long double eps = LONGDOUBLEERROR, d=1.0, u=1.6, v=0.4;	

    int i = ExtremumSimplexND(d,u,v,x,eps,200,xx,f);

	cout << "i = " << i << endl << endl;

	for(i=0; i<3; i++)
		cout << "x(0) = " << xx(0,i) << "\t x(1) = " << xx(1,i)
									 << "\t f = " << f[i] << endl;
	cout << endl;

    for(i=0; i<2; i++)
		cout << "x(" << i << ") = " << x[i] << endl;
	cout << endl;

    cout << "J = " << x[2] << endl;
}

//计算f(X)函数值
template <class _Ty> 
_Ty FunctionValueESND(valarray<_Ty>& x, int n)
{
	_Ty y;
	
    y = x[1] - x[0] * x[0];
	y = 100.0 * y * y;
    y = y + (1.0 - x[0]) * (1.0 - x[0]);

    return(y);
}


