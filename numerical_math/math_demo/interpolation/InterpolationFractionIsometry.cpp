//InterpolationFractionIsometry.cpp  
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
//连分式等距插值

//#include <iostream.h>		//输入输出流头文件
//#include "Interpolation.h"	//插值头文件

int main()
{
	double x0(-1.0), h(0.2), t, s;

	double y[11] = 
	{
		0.0384615, 0.0588236, 0.1, 0.2, 0.5, 
		1.0,       0.5,       0.2, 0.1, 0.0588236, 0.0384615
	};
	
	valarray<double> yy(y,11);

   	cout << " InterpolationFractionIsometry() " << endl;
		
	t = -0.75;
	cout << endl << " t = " << t;
	s = InterpolationFractionIsometry(x0,h,yy,t);
    cout << "\t s1 = " << s << endl;
    
	t = -0.05;
	cout << " t = " << t;
	s = InterpolationFractionIsometry(x0,h,yy,t);
    cout << "\t s2 = " << s << endl;
}
