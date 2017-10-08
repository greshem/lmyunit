//RootAitken.cpp			Aitken法求解非线性方程一个实根
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
	int js(20), k;
    long double eps = 0.0000001, x = 0;
        
	cout << "RootNewton()" << endl << endl;

    k = RootAitken(x, eps, js);

    if (k >= 0)
		cout << "k = " << k << "\t x = " << x << endl;
}

//*	计算函数值
template <class _Ty>
_Ty FunctionValueRA(_Ty dx)
{
	_Ty dCoff[3] = {6, 0, -1}, dValue;

	valarray<_Ty> vdCoff(dCoff, 3);

	dValue = PolyValueOneDim(vdCoff, 3, dx);	//计算多项式值
	
	return(dValue);	
}
