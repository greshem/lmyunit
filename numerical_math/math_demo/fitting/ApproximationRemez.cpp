//ApproximationRemez.cpp
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
//最佳一致逼近多项式里米兹法

#include <iostream>					//模板类输入输出流标准头文件
//#include "FittingApproximation.h"	//拟合与逼近头文件
using namespace std;				//名字空间

int main(void)
{	
	valarray<double> p(5);

	double a(-1), b(1), eps(DOUBLEERROR);

	//最佳一致逼近多项式里米兹法
	ApproximationRemez(a,b,p,eps);

	for(int i=0; i<4; i++)
		cout << "p[" << i << "] = " << p[i] << endl;
	
	cout << endl << "MAX(p-f) = " << p[4] << endl;
}

//计算函数值
template <class _Ty>
_Ty FunctionValueAR(_Ty x)
{
	_Ty y = exp(x);
    return(y);
}


