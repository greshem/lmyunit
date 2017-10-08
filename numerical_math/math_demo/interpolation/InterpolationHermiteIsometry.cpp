//InterpolationHermiteIsometry.cpp  
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
//埃米尔特等距插值

//#include <iostream.h>		//输入输出流头文件
//#include "Interpolation.h"	//插值头文件

int main()
{
	double x, h, t, s;

	double y[10] = 
	{
		0.904837, 0.818731, 0.740818, 0.670320, 0.606531,
		0.548812, 0.496585, 0.449329, 0.406570, 0.367879
	};
	
	valarray<double> yy(y,10);
	valarray<double> dy(10);

	for(int i = 0; i < 10; i ++) dy[i] = -y[i];
	
	x = 0.1;
	h = 0.1;

	cout << " InterpolationHermiteIsometry()" << endl << endl;
	
	t = 0.752;
	cout << " t = " << t;
	s = InterpolationHermiteIsometry(x,h,yy,dy,t);
    cout << "\t s = " << s << endl;
}


