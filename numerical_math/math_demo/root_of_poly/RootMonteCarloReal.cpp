//RootMonteCarloReal.cpp		 
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
//MonteCarlo法求解非线性方程一个实根

#include <iostream>				//输入输出流头文件
//#include "NonLinearEquation.h"	//非线性方程(组)求解头文件
using namespace std;			//名字空间

int main(void)
{
	long double x(0.5);			//自变量
	int m(10);
    long double eps(DOUBLEERROR), b(1);
            
	cout << "RootMonteCarloReal()" << endl << endl;

    RootMonteCarloReal(x,b,m,eps);
    cout << "x = " << x << endl << endl;
}

//*	计算函数值
template <class _Ty>
_Ty FunctionValueMCR(_Ty x)	//f(x)的自变量为实数
{
	_Ty y;
	
	y = exp(-x*x*x) - sin(x) / cos(x) + 800.0;
		
	return(y);
}

