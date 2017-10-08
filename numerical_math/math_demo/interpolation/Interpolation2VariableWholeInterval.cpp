//Interpolation2VariableWholeInterval.cpp  
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
//二元全区间插值

//#include <iostream.h>		//输入输出流头文件
//#include "Interpolation.h"	//插值头文件

int main()
{
	int  i, j;
	double u, v, w;

	valarray<double> x(11), y(11);
    
	for(i=0; i<11; i++)
	{
		x[i] = 0.1 * i;
		y[i] = x[i];
	}

	matrix<double> z(11,11);

	for(i=0; i<11; i++)
	{
		for(j=0; j<11; j++)
		{
			z(i,j) = exp( -(x[i] - y[j]) );
		}

	}
	
	cout << "Interpolation2VariableWholeInterval()" << endl << endl;

	u = 0.35;	v = 0.65;
	w = Interpolation2VariableWholeInterval(x, y, z, u, v);
    cout << "x = 0.35    	y = 0.65         z(x,y) = " << w << endl;
		
	u = 0.45;	v = 0.55;
	w = Interpolation2VariableWholeInterval(x, y, z, u, v);
    cout << "x = 0.45    	y = 0.55         z(x,y) = " << w << endl;
}


