//InterpolationHermiteNotIsometry.cpp  
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
//埃米尔特不等距插值

//#include <iostream.h>		//输入输出流头文件
//#include "Interpolation.h"	//插值头文件

int main()
{
	double t,s;

	double x[10] = 
	{
		0.1, 0.15, 0.30, 0.45, 0.55, 
		0.6, 0.7,  0.85, 0.9,  1.0
	};
    
	double y[10] =
	{
		0.904837, 0.860708, 0.740818, 0.637628, 0.576950,
		0.548812, 0.496585, 0.427415, 0.406570, 0.367879
	};

	valarray<double> dy(10);
	valarray<double> yy(y,10);
    valarray<double> xx(x,10);

  	for(int i = 0; i < 10; i++) dy[i] = -y[i];
     	
	cout << " InterpolationHermiteNotIsometry()" << endl;
	
	t = 0.356;
	cout << endl << " t = " << t;
	s = InterpolationHermiteNotIsometry(xx,yy,dy,t);
    cout << "\t s = " << s << endl;	
}
