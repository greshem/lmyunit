//RootLeastSquareGeneralizedInverse1.cpp
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
//非线性方程组最小二乘解的广义逆法示例1

#include <iostream>				//输入输出流头文件
//#include "LinearEquation.h"		//线性方程组求解头文件
//#include "NonLinearEquation.h"	//非线性方程(组)求解头文件
using namespace std;			//名字空间

int main(void)
{	
	int m(2), i, ka(3);
    double eps1(FLOATERROR), eps2(FLOATERROR);
    valarray<double> x(2);
	
	x[0] = 0.5;
	x[1] = -1.0;
        
	cout << "RootLeastSquareGeneralizedInverse1()" << endl;

	i = RootLeastSquareGeneralizedInverse(m, eps1, eps2, x, ka);

    cout << endl;
	cout << "i= " << i << endl << endl;
	
    for (int it=0; it < 2; it++)
		cout << "x(" << it << ") = " << x[it] << endl;

	cout<<endl;
}

//计算非线性方程组左边函数值
template <class _Ty>
void FunctionValueRLSGI(valarray<_Ty>& x,valarray<_Ty>& d)
{ 
	d[0] = x[0] * x[0] + 10.0 * x[0] * x[1] + 4.0 * x[1] * x[1] + 0.7401006;
    d[1] = x[0] * x[0] - 3.0 * x[0] * x[1] + 2.0 * x[1] * x[1] - 1.0201228;
}

//计算雅可比矩阵
template <class _Ty>
void JacobiMatrix(valarray<_Ty>& x, matrix<_Ty>& p)
{
	p(0,0) = 2.0 * x[0] + 10.0 * x[1];
    p(0,1) = 10.0 * x[0] + 8.0 * x[1];
    p(1,0) = 2.0 * x[0] - 3.0 * x[1];
    p(1,1) = -3.0 * x[0] + 4.0 * x[1];
}

