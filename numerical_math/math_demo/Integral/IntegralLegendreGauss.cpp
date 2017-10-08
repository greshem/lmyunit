//IntegralLegendreGauss.cpp	 勒让德-高斯法求积
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
	double eps = FLOATERROR, a(2.5), b(8.4);
    
	double dValue = IntegralLegendreGauss(a, b, eps);

	cout << "IntegralLegendreGauss()" << endl << endl;

	cout << "dValue = " << dValue << endl << endl;
}

// 计算被积函数值
template <class _Ty>
_Ty FunctionValueLegG(_Ty x)
{
	_Ty dValue;
	
	dValue= x * x + sin(x);

    return(dValue);
}
