//HessenbergTransform.cpp  
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
//约化一般实矩阵为赫申伯格阵的初等相似变换法

#include <iostream>				//输入输出流头文件
//#include "Matrix.h"				//矩阵类及相关函数头文件
//#include "EigenvalueVector.h"	//特征值及特征向量头文件
using namespace std;			//名字空间

int main()						// 定义控制台应用程序的入口点
{
	double a[5][5] = 
	{
		{  1.0,   6.0, -3.0, -1.0,  7.0},
		{  8.0, -15.0, 18.0,  5.0,  4.0},
		{ -2.0,  11.0,  9.0, 15.0, 20.0},
		{-13.0,   2.0, 21.0, 30.0, -6.0},
		{ 17.0,  22.0, -5.0,  3.0,  6.0} 
	};

	matrix<double> da(&a[0][0],5,5);

	
	cout.setf(ios::fixed);	//输出数据为定点法
	cout.precision(6);		//精度6位

	int iRet = HessenbergTransform(da);

	if(iRet > 0)
	{
		cout << "MATRIX A IS: " << endl;
		MatrixLinePrint(da);
		cout << endl;
	}
}

