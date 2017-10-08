//IntegralFraction1D.cpp	一维连分式法求积
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

#include <iostream>			//输入输出流头文件
//#include "Integral.h"		//积分头文件
using namespace std;		//名字空间

int main(void)
{	
	double eps = FLOATERROR, a(0), b(4.3);

	cout << "IntegralFraction1D()" << endl << endl;

	double dIntegralValue = IntegralFraction1D(a,b,eps);

	cout << "IntegralValue = " << dIntegralValue << endl << endl;
}

// 计算被积函数值
template <class _Ty>
_Ty FunctionValueF1D(_Ty x)
{
	_Ty y;

	y = exp(-x * x);
    
	return(y);
}



