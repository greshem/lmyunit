//RootMonteCarloGroupReal.cpp	MonteCarlo法求解非线性方程组一组实根
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

#include <iostream>				//输入输出流头文件
//#include "NonLinearEquation.h"	//非线性方程(组)求解头文件
using namespace std;			//名字空间

int main(void)
{
	size_t m(10), n(3), i;
	valarray<double> x(3);		//自变量
	double eps(DOUBLEERROR), b(2);
    
	x[0] = x[1] = x[2] = 0;
	        
	cout << "RootMonteCarloGroupReal()" << endl << endl;

    RootMonteCarloGroupReal(x,b,m,eps);

    for(i = 0; i < n; i++)
		cout << "x(" << i << ") = " << x[i] << endl;
}

//*	计算函数模
template <class _Ty>
_Ty FunctionModule(valarray<_Ty> x)	//f(x)的系数及自变量为实数
{
	_Ty f,f1,f2,f3;

    f1 = 3.0*x[0]+x[1]+2.0*x[2]*x[2]-3.0;
    f2 = -3.0*x[0]+5.0*x[1]*x[1]+2.0*x[0]*x[2]-1.0;
    f3 = 25.0*x[0]*x[1]+20.0*x[2]+12.0;
    f = sqrt(f1*f1+f2*f2+f3*f3);
    return(f);
}

