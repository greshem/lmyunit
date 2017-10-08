//LE_IllConditionedEquation.cpp  病态方程组的求解 
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
	int k;
    double eps, x[4] = {0.0};
    double a[4][4] =
	{
		{ 3.4336,   -0.5238,   0.67105, -0.15272},
		{-0.5238,    3.28326, -0.73051, -0.2689},
		{ 0.67105,  -0.73051,  4.02612,  0.01835},
		{-0.15272,  -0.2689,   0.01835,  2.75702}
	};
    
	double b[4] = { -1.0, 1.5, 2.5, -2.0};
	
	valarray<double> bb(b, 4);
	valarray<double> xx(x, 4);
	matrix<double> aa(&a[0][0], 4, 4);
	
	eps = FLOATERROR;
    
	if(LE_IllConditionedEquation(aa, bb, eps, xx) > 0)
	{
        for(k = 0; k < 4; k ++)
		{
			cout << "x[" << k << "] = " << xx[k] << endl;
		}
	}

	cout << endl;
}
