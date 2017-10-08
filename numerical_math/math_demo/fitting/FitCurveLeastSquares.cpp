//FitCurveLeastSquares.cpp
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
//最小二乘曲线拟合

#include <iostream>					//模板类输入输出流标准头文件
//#include "FittingApproximation.h"	//拟合与逼近头文件
using namespace std;				//名字空间

int main(void)
{	
	valarray<double> x(20), y(20), da(6), dt(3);

	int i=0;
	for(int i=0; i<20; i++)
	{
		x[i] = 0.1 * i;
        y[i] = x[i] - exp(-x[i]);
    }
	
	cout.setf(ios::fixed);	//输出数据为定点法
	cout.precision(14);		//精度14位
	//##2010_09_26_22:39:30 add by greshem
	FitCurveLeastSquares(x,y,da,dt);

	for (i=0; i<6; i++)
		cout << "da[" << i << "] = " << da[i] << endl;
	
	cout << endl;

	for (i=0; i<3; i++)
		cout << "dt[" << i << "] = " << dt[i] << endl;
}

