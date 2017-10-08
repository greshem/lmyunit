//LE_LinearLeastSquareHouseholder.cpp   
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
//求解线性最小二乘问题的豪斯荷尔德变换法

#include <iostream>			//输入输出流头文件
//#include "LinearEquation.h"	//线性方程(组)求解头文件

int main()
{
	int i;
    double a[4][3] = 
	{
		{ 1.0,  1.0, -1.0},
		{ 2.0,  1.0,  0.0},
		{ 1.0, -1.0,  0.0},
		{-1.0,  2.0,  1.0}
	};
    
	double b[4] = {2.0, -3.0, 1.0, 4.0};
    
	matrix<double> qq(4, 4);
	valarray<double> bb(b, 4);
	matrix<double> aa(&a[0][0], 4, 3);
   
	i = LE_LinearLeastSquareHouseholder(aa, bb, qq);
    
	if(i != 0)
	{
		for(int s = 0; s < 3; s++)
		{
			cout << "x(" << s << ") = " << bb[s] << endl;
		}
		cout << endl;

		cout << "MAT Q IS: " << endl;
		MatrixLinePrint(qq);
		cout << endl;

        cout << "MAT R IS: " << endl;
        MatrixLinePrint(aa);
	}

	cout << endl;
}

