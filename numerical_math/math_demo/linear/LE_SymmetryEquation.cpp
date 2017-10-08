//LE_SymmetryEquation.cpp	求解对称方程组的分解法
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

#include <iostream>			//输入输出流头文件
//#include "LinearEquation.h"	//线性方程(组)求解头文件

int main()
{
	int i;
    
	double a[5][5] = 
	{
		{5.0, 7.0,  6.0,  5.0,  1.0},
		{7.0, 10.0, 8.0,  7.0,  2.0},
		{6.0, 8.0,  10.0, 9.0,  3.0},
		{5.0, 7.0,  9.0,  10.0, 4.0},
		{1.0, 2.0,  3.0,  4.0,  5.0}
	};

    double c[5][2] = 
	{
		{24.0,  96.0},
		{34.0, 136.0},
		{36.0, 144.0},
		{35.0, 140.0},
		{15.0,  60.0}
	};

	matrix<double> aa(&a[0][0], 5, 5);
	matrix<double> cc(&c[0][0], 5, 2);
	
  	cout.setf(ios::fixed);	//输出数据为定点法
	cout.precision(6);		//精度6位

	if(LE_SymmetryEquation(aa, cc) > 0)
	{
		cout.width(22);
		cout << "Group 1";
		cout.width(16);
		cout << "Group 2" << endl << endl;

		for(i = 0; i < 5; i++)
		{
			cout << "x(" << i << ") = ";
			MatrixLinePrint(cc, i);
		}
	}
	cout << endl;
}

