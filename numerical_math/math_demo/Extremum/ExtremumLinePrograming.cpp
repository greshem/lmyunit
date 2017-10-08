//ExtremumLinePrograming.cpp	线性规划
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

#include <iostream>		//模板类iostream输入输出流标准头文件
//#include "Extremum.h"	//极值头文件

int main(void)
{	
	long double aa[3][6] = 
	{
		{1, 2,  7, 1, 0, 0},
		{1, 4, 13, 0, 1, 0},
		{0, 2,  8, 0, 0, 1}	
	};
	
	long double bb[3] = {10, 18, 13};
	long double cc[6] = {-4, -9, -26, 0, 0, 0};

	matrix<long double> a(&aa[0][0], 3, 6);
	valarray<long double> x(6), b(bb, 3), c(cc, 6);

	int iValue=ExtremumLinePrograming(a,b,c,x);
	
	if(iValue != 0)
	{
		for (iValue = 0; iValue < 6; iValue++)
			cout << "x(" << iValue << ") = " << x[iValue] << endl;
	}
}

