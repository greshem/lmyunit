//RootQuasiNewton.cpp			拟牛顿法求解非线性方程组一组实根
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
//#include "polynomials.h"		//多项式及连分式求值头文件
//#include "NonLinearEquation.h"	//非线性方程(组)求解头文件
using namespace std;			//名字空间

int main(void)
{	
	int k = 100, i;
    double eps = 0.000001, x[3] = {1.0, 1.0, 1.0}, t = 0.1, h = 0.1;
    valarray<double> vx(x, 3);
        
	cout << "RootQuasiNewton()" << endl << endl;

    i = RootQuasiNewton(eps, t, h, vx, k);		//求根
	
	cout << "i = " << i << endl << endl;

	for(i = 0; i < 3; i++)
		cout << "x(" << i << ") = " << vx[i] << endl;

	cout << endl;
}

//*	计算函数值
template <class _Ty> 
void FunctionValueRSN(valarray<_Ty>& x, valarray<_Ty>& y)
{
	y[0]=x[0]*x[0]+x[1]*x[1]+x[2]*x[2]-1.0;	//计算多项式f0函数值
    y[1]=2.0*x[0]*x[0]+x[1]*x[1]-4.0*x[2];	//计算多项式f1函数值
    y[2]=3.0*x[0]*x[0]-4.0*x[1]+x[2]*x[2];	//计算多项式f2函数值
}
