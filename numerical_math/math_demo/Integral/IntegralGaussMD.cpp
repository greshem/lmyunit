//IntegralGaussMD.cpp	 多重高斯法求积
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

#include <iostream>		//输入输出流头文件
//#include "Integral.h"	//积分头文件
using namespace std;	//名字空间

int main(void)
{
	long double js[3]={4,4,4}; 

	valarray<long double> vjs(js, 3);

	long double dValue = IntegralGaussMD(vjs);
	
	cout << "IntegralGaussMD()" << endl << endl;

	cout << "dValue = " << dValue << endl << endl;
}

//计算各层积分上、下限值
template <class _Ty>
void FunctionBoundaryGMD(int j, valarray<_Ty>& x, valarray<_Ty>& y)
{
	  switch(j)
      { 
	    case 0:	{
					y[0] = 0.0;
					y[1] = 1.0;
					break;
				}
        case 1: {
					y[0] = 0.0;
					y[1] = sqrt(1.0-x[0]*x[0]);
					break;
				}
        case 2: {
					_Ty q = x[0]*x[0]+x[1]*x[1];
					y[0] = sqrt(q);
					y[1] = sqrt(2.0-q);
					break;
                }
	  }
}

//计算被积函数值
template <class _Ty>
_Ty FunctionValueGMD(valarray<_Ty>& x)
{
	_Ty dValue;
	
	dValue = x[2] * x[2];

    return(dValue);
}

