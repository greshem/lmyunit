//FitSurfaceLeastSquares.cpp
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
//矩形域的最小二乘曲面拟合

#include <iostream>					//模板类输入输出流标准头文件
//#include "FittingApproximation.h"	//拟合与逼近头文件
using namespace std;				//名字空间

int main(void)
{	
	int i, j;
	matrix<double> z(11,21), a(6,5);
	valarray<double> x(11), y(21), dt(3);

	for(i=0; i<11; i++) x[i]=0.2*i;

    for(i=0; i<21; i++) y[i]=0.1*i;
    
	for(i=0; i<11; i++)
      for(j=0; j<21; j++)
        z(i,j)=exp(x[i]*x[i]-y[j]*y[j]);

	cout.setf(ios::fixed);	//输出数据为定点法
	cout.precision(6);		//精度6位

	FitSurfaceLeastSquares(x,y,z,a,dt);

	cout << "MAT A(i,j) IS: " << endl << endl;

	MatrixLinePrint(a);

	cout << endl << "\t";

	for(i=0; i<3; i++)
		cout << "dt(" << i << ") = " << dt[i] << "\t";

	cout << endl;
}

