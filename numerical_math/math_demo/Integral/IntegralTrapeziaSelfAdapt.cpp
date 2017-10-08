//IntegralTrapeziaSelfAdapt.cpp		
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
//自适应梯形法求积

#include <iostream>			//输入输出流头文件
//#include "Integral.h"		//积分头文件
using namespace std;		//名字空间

int main(void)
{	
	double eps = FLOATERROR, a(-1), b(1), d(0.0001);
            
	cout << "IntegralTrapeziaSelfAdapt()" << endl << endl;

	double dIntegralValue = IntegralTrapeziaSelfAdapt(a,b,eps,d);

	cout << "IntegralValue = " << dIntegralValue << endl << endl;
}

// 计算被积函数值
template <class _Ty>
_Ty FunctionValueITSA(_Ty x)
{
	_Ty y;

	y = 1.0 / (1.0 + 25.0 * x * x);

    return(y);
}


