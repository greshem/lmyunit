//EigenvalueVectorRealTriangleQR.cpp  
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
//实对称三角阵全部特征值及特征向量QR法

#include <iostream>				//输入输出流头文件
//#include "Matrix.h"				//矩阵类及相关函数头文件
//#include "EigenvalueVector.h"	//特征值及特征向量头文件

using namespace std;			//名字空间

int main()						// 定义控制台应用程序的入口点
{
	double a[5][5] = 
	{	
		{10.0,  1.0,  2.0,  3.0,  4.0},
        { 1.0,  9.0, -1.0,  2.0, -3.0},
        { 2.0, -1.0,  7.0,  3.0, -5.0},
        { 3.0,  2.0,  3.0, 12.0, -1.0},
		{ 4.0, -3.0, -5.0, -1.0, 15.0} 
	};

	valarray<double> b(5), c(5);
	matrix<double> q(5,5), da(&a[0][0],5,5);

	double eps = FLOATERROR;
	
  	cout.setf(ios::fixed);	//输出数据为定点法
	cout.precision(6);		//精度6位

	HouseholderTransform(da,q,b,c);
	int k = EigenvalueVectorRealTriangleQR(b,c,q,eps,60);

	cout << "MATRIX A IS: " << endl;
    MatrixLinePrint(da);
    cout << endl;

	if(k>0)
	{
		cout << "MATRIX B IS: " << endl;
		ValarrayPrint(b);
		cout << endl;

		cout << "MATRIX Q IS: " << endl;
		MatrixLinePrint(q);
		cout << endl;
	}
}

