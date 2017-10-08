//RootNewton.cpp				Newton法求解非线性方程一个实根
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
	int js = 60, k;
    long double eps = 0.000001, x = 1.5;
    
	cout << "RootNewton()" << endl << endl;

    k = RootNewton(x,eps,js);		//求根

    if(k >= 0)
		cout << "k = " << k << "  x = " << x << endl;
}

//*	计算函数及导数值 
template <class _Ty>
void FunctionValueRN(_Ty dx, valarray<_Ty>& y)
{
	_Ty dCoff0[4] = {-1, 0, -1, 1};
	_Ty dCoff1[3] = {0, -2, 3};

	valarray<_Ty> vdCoff0(dCoff0,4), vdCoff1(dCoff1,3);

	y[0] = PolyValueOneDim(vdCoff0, 4, dx);	//计算多项式值
	y[1] = PolyValueOneDim(vdCoff1, 3, dx);	//计算多项式导数值
}
