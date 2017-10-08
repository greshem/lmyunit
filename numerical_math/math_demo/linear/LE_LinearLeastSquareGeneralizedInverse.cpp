//LE_LinearLeastSquareGeneralizedInverse.cpp  
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
//求解线性最小二乘问题的广义逆法 

#include <iostream>				//输入输出流头文件
//#include "LinearEquation.h"		//线性方程(组)求解头文件

int main()
{ 
	int i;
    
	double a[4][3] = 
	{
		{ 1.0,  1.0, -1.0},
		{ 2.0,  1.0,  0.0},
		{ 1.0, -1.0,  0.0},
		{-1.0,  2.0,  1.0}
	};
    
	matrix<double> ta(&a[0][0], 4, 3);
	
	double b[4] = {2.0, -3.0, 1.0, 4.0};

    valarray<double> bb(b, 4);
    valarray<double> xx(3);
	matrix<double> taa(3, 4);
	matrix<double> uu(4, 4);
	matrix<double> vv(3, 3);

    double eps = FLOATERROR;
    
	i = LE_LinearLeastSquareGeneralizedInverse(ta, bb, xx, taa, eps, uu, vv);
    
  	cout.setf(ios::fixed);	//输出数据为定点法
	cout.precision(6);		//精度6位

	if (i>0)
	{ 
		for(i = 0; i < 3; i ++)
		{
			cout << "x(" << i << ") = " << xx[i] << endl;
		}
		cout << endl;	
        
		cout << "MAT A+ : " << endl;
		MatrixLinePrint(taa);
        cout << endl;
   }
}

