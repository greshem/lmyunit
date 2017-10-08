//EigenvalueVectorRealSymmetryJacobi.cpp  
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
//实对称阵特征值及特征向量雅可比法

#include <iostream>				//输入输出流头文件
//#include "Matrix.h"				//矩阵类及相关函数头文件
//#include "EigenvalueVector.h"	//特征值及特征向量头文件
using namespace std;			//名字空间

int main()						// 定义控制台应用程序的入口点
{
	double a[3][3] = 
	{
		{ 2.0, -1.0,  0.0},
		{-1.0,  2.0, -1.0},
		{ 0.0, -1.0,  2.0}
	};
	
	matrix<double> v(3,3), da(&a[0][0],3,3);
	double eps = FLOATERROR;
	
  	cout.setf(ios::fixed);	//输出数据为定点法
	cout.precision(6);		//精度6位

	int k = EigenvalueVectorRealSymmetryJacobi(da, v, eps, 100);
	if(k > 0)
	{
		cout << "MATRIX A IS: " << endl;
		MatrixLinePrint(da);
		cout << endl;

		cout << "MATRIX V IS: " << endl;
		MatrixLinePrint(v);
		cout << endl;
	}

	double dmb[3][3] = 
	{
		{  3.0, -3.0, -2.0 },
		{ -3.0,  8.0,  4.0 },
		{  -2.0, 4.0,  3.0 } 
	};

}




