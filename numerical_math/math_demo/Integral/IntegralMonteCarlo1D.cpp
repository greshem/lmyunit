//IntegralMonteCarlo1D.cpp	 蒙特卡洛法求积
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
	double a(2.5), b(8.4);
    
	double dValue = IntegralMonteCarlo1D(a, b);	//调用求积函数

	cout << "IntegralMonteCarlo1D()" << endl << endl;

	cout << "dValue = " << dValue << endl << endl;
}

//计算被积函数值
template <class _Ty>
_Ty FunctionValueMC1D(_Ty x)		
{
	_Ty dValue;
	
	dValue = x * x + sin(x);

    return(dValue);
}

