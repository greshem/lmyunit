// MatrixRank.cpp		用全选主元高斯消元法求一般矩阵的秩
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

//#include <fstream>	//文件流头文件
#include <iostream>		//输入输出流
//#include "Matrix.h"		//矩阵类及相关函数等的定义
using namespace std;	//名字空间

int main()				// 定义控制台应用程序的入口点
{
	size_t mRank;
#include "a.cpp";
#include "b.cpp";
#include "c.cpp";


	const matrix<double> matA(&a[0][0], 10, 10);
	const matrix<double> matB(&b[0][0], 10, 10);
	const matrix<double> matC(&c[0][0], 10, 10);

	mRank = MatrixRank(matA);
	cout << endl << "The rank of matA is : " << mRank << endl;

	mRank = MatrixRank(matB);
	cout << endl << "The rank of matB is : " << mRank << endl;

	mRank = MatrixRank(matC);
	cout << endl << "The rank of matC is : " << mRank << endl;
}

