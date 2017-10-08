//IntegralSimpson1D.cpp		 变步长辛卜生法求积
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
	double eps = FLOATERROR, a(0), b(1);
                
	cout << "IntegralSimpson1D()" << endl << endl;

	double t = IntegralSimpson1D(a, b, eps);

	cout << "t = " << t << endl << endl;
}

// 计算被积函数值
template <class _Ty>
_Ty FunctionValueIS1D(_Ty x)
{
	_Ty y;

	y = log(1.0 + x) / (1.0 + x * x);
    
	return(y);
}


