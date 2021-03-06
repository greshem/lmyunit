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
//全选主元高斯-约当(Gauss-Jordan)法求矩阵逆

#include <iostream>		//输入输出流
//#include "Matrix.h"		//矩阵类及相关函数等的定义
using namespace std;	

int main()				// 定义控制台应用程序的入口点
{
	const double dma[4][4] =
	{
		{0.2368,0.2471,0.2568,1.2671},
		{1.1161,0.1254,0.1397,0.1490},
		{0.1582,1.1675,0.1768,0.1871},
		{0.1968,0.2071,1.2168,0.2271} 
	};

	
	matrix<double> matA(&dma[0][0], 4, 4);
	matrix<double> matB(matA);
		
	cout << "matA : " << endl;
	MatrixLinePrint(matA);			//按行输出矩阵matA

	if(MatrixInversionGS(matA)>0)	//调用求逆函数，判断是否>0
	{
		cout << endl << "Inversion(matA) : " << endl;
	
		MatrixLinePrint(matA);		//按行输出矩阵matA的逆
	
		cout << endl << "Inversion(matA) * matA : " << endl;

		matA = matA * matB;
		MatrixLinePrint(matA);		//按行输出矩阵matA与其逆的乘积
	}
}
