//LE_TridiagonalEquationGauss.cpp    求解三对角线方程组的追赶法 
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

//#include <iostream.h>				//输入输出流头文件
//#include "LinearEquation.h"			//线性方程(组)求解头文件

int main()
{
	int i;
    double b[13] =
	{
		13.0, 12.0, 
			11.0, 10.0, 9.0, 
				8.0, 7.0, 6.0, 
					5.0, 4.0, 3.0, 
							2.0, 1.0
	};
    double d[5] = {3.0, 0.0, -2.0, 6.0, 8.0};

	valarray<double> bb(b,13);
	valarray<double> dd(d,5);
	
    if(LE_TridiagonalEquationGauss(bb, dd) > 0)
	{
		for (i = 0; i < 5; i++)
			cout << "x(" << i << ") = " << dd[i] << endl;
	}
	cout << endl;
}
