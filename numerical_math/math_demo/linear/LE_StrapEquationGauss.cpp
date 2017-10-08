//LE_StrapEquationGauss().cpp	一般带型方程组的求解
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
//#include "LinearEquation.h"		//线性方程(组)求解头文件

int main()
{
	double b[8][5] = 
	{
		{ 3.0, -4.0,  1.0, 0.0,  0.0},
		{-2.0, -5.0,  6.0, 1.0,  0.0},
		{ 1.0,  3.0, -1.0, 2.0, -3.0},
		{ 2.0,  5.0, -5.0, 6.0, -1.0},
		{-3.0,  1.0, -1.0, 2.0, -5.0},
		{ 6.0,  1.0, -3.0, 2.0, -9.0},
		{-4.0,  1.0, -1.0, 2.0,  0.0},
		{ 5.0,  1.0, -7.0, 0.0,  0.0}
	};
    
	double d[8][3] = 
	{
		{ 13.0,  29.0, -13.0},
		{ -6.0,  17.0, -21.0},
		{-31.0,  -6.0,   4.0},
		{ 64.0,   3.0,  16.0},
		{-20.0,   1.0,  -5.0},
		{-22.0, -41.0,  56.0},
		{-29.0,  10.0, -21.0},
		{  7.0, -24.0,  20.0}
	};
	
	matrix<double> bb(&b[0][0], 8, 5);
	matrix<double> dd(&d[0][0], 8, 3);
	
    if(LE_StrapEquationGauss(bb, dd, 2, 5) > 0)
	{
		cout.width(12);
		cout << "Group 1";
		cout.width(16);
		cout << "Group 2";
		cout.width(16);
		cout << "Group 3" << endl << endl;
		MatrixLinePrint(dd);
	}
	cout << endl;	
}

