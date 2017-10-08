//RootHalves.cpp		二分法求解非线性方程示例
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
    size_t m = 6;					//估计实根个数
    size_t rootNo;					//返回搜索到的实根个数
	valarray<long double> x(6);		//搜索到的实根

	long double a = -2.0, b = 5.0, step = 0.2, eps = FLOATERROR;

    rootNo = RootHalves(a, b, step, eps, x, m);		//求根
	
	cout << "The amount of root is : " << rootNo << endl << endl;

    for(size_t i = 0; i < rootNo; i++)
		cout << "x(" << i << ") = " << x[i] << endl;
}

//*	计算f(x)函数值
template <class _Ty> 
_Ty FunctionValueRH(_Ty dx)
{
	_Ty dCoff[7] = {-20,7,-7,1,3,-5,1}, dValue;

	valarray<_Ty> vdCoff(dCoff, 7);				//多项式系数
	
	dValue = PolyValueOneDim(vdCoff, 7, dx);	//计算多项式值

	return(dValue);
}
