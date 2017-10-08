//LE_GaussSeidelIteration.cpp	高斯-赛德尔迭代法 
//#2010_09_25_19:59:00 add by greshem
//添加矩阵乘法验证的
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
//#include "LinearEquation.h"		//线性方程(组)求解头文件

int main()
{ 
	int i;
    double eps;
    
	double a[4][4] = 
	{
		{7.0,  2.0,  1.0,  -2.0},
		{9.0,  15.0, 3.0,  -2.0},
		{-2.0, -2.0, 11.0,  5.0},
		{1.0,  3.0,  2.0,  13.0}
	};
    
	double b[4] = {4.0, 7.0, -1.0, 0.0};
	double equal[4]={};
   	valarray<double> xx(5);
	valarray<double> bb(b, 4);
	matrix<double> aa(&a[0][0], 4, 4);
	
	eps = FLOATERROR;
	
  	cout.setf(ios::fixed);	//输出数据为定点法
	cout.precision(6);		//精度6位
    
	if(LE_GaussSeidelIteration(aa, bb, xx, eps) > 0)
	{
		for(i = 0; i < 4; i ++)
        {
			cout << "x(" << i << ") = " << xx[i] << endl;
			equal[i]=xx[i];
		}
		matrix<double> matA(&a[0][0], 4, 4);
		matrix<double> matB(&xx[0], 4, 1);
		MatrixLinePrint(matA*matB);	
	}
	cout << endl;
}

