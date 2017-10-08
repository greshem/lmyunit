//EigenvalueVectorHessenbergQR.cpp  求赫申伯格阵全部特征值QR法
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

	valarray<complex<double> > uv(5);
	matrix<double> da(&a[0][0],5,5);
	double eps = FLOATERROR;
	
  	cout.setf(ios::fixed);	//输出数据为定点法
	cout.precision(6);		//精度6位

	if(HessenbergTransform(da) > 0)
	{
		cout << "MATRIX H IS: " << endl;
		MatrixLinePrint(da);
		cout << endl;

		int k = EigenvalueVectorHessenbergQR(da,uv,eps,60);
	
		if(k>0)
		{
			cout << "EIGENVALUE IS: " << endl;
			ValarrayPrint(uv);
			cout << endl;
		}
	}
}




