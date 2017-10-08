//InterpolationAitkenNotIsometry.cpp	
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
//埃特金不等距逐步法插值 

//#include <iostream.h>		//输入输出流头文件
//#include "Interpolation.h"	//插值头文件

int main()
{
	double eps = FLOATERROR, t, z;
	double x[11] = 
	{
		-1.0, -0.8, -0.65, -0.4, -0.3, 
		 0.0,  0.2,  0.4,   0.6,  0.8, 1.0
	};
	
	double y[11] = 
	{
		0.0384615, 0.0588236, 0.0864865, 0.2, 0.307692,
		1.0,       0.5,       0.2,       0.1, 0.0588236, 0.0384615
	};
    
	valarray<double> yy(y,11), xx(x,11);

	cout << " InterpolationAitkenNotIsometry()" << endl << endl;
	
	t = 0.15;
	z = InterpolationAitkenNotIsometry(xx, yy, t, eps);
	cout << " t = " << t << "\t" << "z = " << z << endl;

	t = 0.05;
	z=InterpolationAitkenNotIsometry(xx, yy, t, eps);
	cout << " t = " << t << "\t" << "z = " << z << endl;
}
