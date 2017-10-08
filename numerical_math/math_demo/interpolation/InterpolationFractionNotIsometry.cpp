//InterpolationFractionNotIsometry.cpp  
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
//连分式不等距插值
 
//#include <iostream.h>		//输入输出流头文件
//#include "Interpolation.h"	//插值头文件

int main()
{
	double t, s;

	double x[10] = 
	{
		-1.0, -0.8, -0.65, -0.4, -0.3, 
		 0.0,  0.2,  0.45,  0.8,  1.0
	};

    double y[10] = 
	{
		0.0384615, 0.0588236, 0.0864865, 0.2,       0.307692,
		1.0,       0.5,       0.164948,  0.0588236, 0.0384615
	};

    valarray<double> yy(y,10);
	valarray<double> xx(x,10);
   
   	cout << " InterpolationFractionNotIsometry() " <<endl;
	
	t = -0.85;
	cout << endl << " t = " << t;
	s = InterpolationFractionNotIsometry(xx,yy,t);
    cout << "\t s2 = " << s << endl;
    
	t = 0.25;
	cout<<" t = " << t;
	s = InterpolationFractionNotIsometry(xx,yy,t);
    cout << "\t s3 = " << s << endl;    
}


