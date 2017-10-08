//RootFraction.cpp		Fraction法求解非线性方程一个实根
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
    double eps = DOUBLEERROR, x = 1.0;

	cout << "RootFraction()" << endl << endl;
    
    int k = RootFraction(x, eps);

    if(k >= 0)
		cout << "k = " << k << "  x = " << x << endl;

	cout << endl;
}

//*	计算函数值
template <class _Ty>
_Ty FunctionValueRF(_Ty dx) 
{
	_Ty dCoff[4]={-1, 0, -1, 1}, dValue;

	valarray<_Ty> vdCoff(dCoff, 4);

	dValue = PolyValueOneDim(vdCoff, 4, dx);	//计算多项式值
	
	return(dValue);
}
