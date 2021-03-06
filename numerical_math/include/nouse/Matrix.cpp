//########################################################################
//#include <QzjUnit.hpp>
//#include <MLmyUnit.hpp>
#include <Baselib.hpp>
#include <gtest/gtest.h>
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

#include "Matrix.hpp"
//MatrixDeterminant.cpp  高斯全选主元法矩阵求行列式

//#include <fstream>	//文件流头文件
#include <iostream>		//输入输出流
using namespace std;	//名字空间

int main()				// 定义控制台应用程序的入口点
{
	const double dma[4][4] = 
	{
		{  1.0,  2.0,  3.0,  4.0 },
		{  5.0,  6.0,  7.0,  8.0 },
		{  9.0, 10.0, 11.0, 12.0 },
		{ 13.0, 14.0, 15.0, 16.0 }
	};

	const double dmb[4][4] = 
	{
		{  3.8, -3.0, -2.0,  4.0 },
		{  5.0, -5.2,  1.0,  8.0 },
		{ 11.0,  8.0,  5.6, -7.0 },
		{  5.0, -1.0, -3.0, -1.4 } 
	};

	const matrix<double> matA(&dma[0][0], 4, 4);
	const matrix<double> matB(&dmb[0][0], 4, 4);

	cout << "Det(matA) = " << MatrixDeterminant(matA) << endl;

	cout << endl << "Det(matB) = " << MatrixDeterminant(matB) << endl;
	
	const int imc[3][3] = 
	{
		{-1, 2, 3}, 
		{ 9, 0, 2},
		{ 5, 1, 6}
	};

	const matrix<int> matC(&imc[0][0], 3, 3);
	cout << endl << "Det(matC) = " << MatrixDeterminant(matC) << endl;
	return 0;
}

