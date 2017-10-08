//InterpolationAitkenIsometry.cpp
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
//埃特金等距逐步法插值

//#include <iostream.h>		//输入输出流头文件
//#include "Interpolation.h"	//插值头文件

int main(void)
{	
	double eps = LONGDOUBLEERROR, t, x(0.1), h(0.1), z;

    double y[10] = 
	{
		0.904837, 0.818731, 0.740818, 0.670320,	0.606531, 
		0.548812, 0.496585, 0.449329, 0.406570, 0.367879
	};

    valarray<double> yy(y,10);

	cout << " InterpolationAitkenIsometry()" << endl << endl;

	t = 0.15;
	z = InterpolationAitkenIsometry(x, h, yy, t, eps);
	cout << " t = " << t << "\t" << "z = " << z << endl;

	t = 0.55;
	z=InterpolationAitkenIsometry(x, h, yy, t, eps);
	cout << " t = " << t << "\t" << "z = " << z << endl;
}
 
