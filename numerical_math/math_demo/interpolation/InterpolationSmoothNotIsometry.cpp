//InterpolationSmoothNotIsometry.cpp	
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
//光滑不等距插值

//#include <iostream.h>			//输入输出流头文件
//#include "Interpolation.h"		//插值头文件

int main()
{
	int k(-1), n(11);
	
	double x[11] = 
	{
		-1.0, -0.95, -0.75, -0.55, -0.3, 
		 0.0,  0.2,   0.45,  0.60,  0.80, 1.0
	};
	
	double y[11] = 
	{
		0.0384615, 0.0424403, 0.06639,  0.116788,  0.307692, 1.0, 
		0.5,       0.164948,  0.1,      0.0588236, 0.0384615
	};

	valarray<double> xx(x,11);
	valarray<double> yy(y,11);
	valarray<double> ss(5);

	cout << " InterpolationSmoothNotIsometry()" << endl << endl;
	
	double t = -0.85;
	cout << " x = " << t;
	InterpolationSmoothNotIsometry(xx, yy, k, t, ss);
	cout << "\tf(x) = " << ss[4] << endl;
    cout<<" s0 = "<<ss[0]<<"\ts1 = "<<ss[1]<<"\ts2 = "<<ss[2]<<"\ts3 = "<<ss[3]<<endl;
	
	t = 0.95;
	cout << endl << " x = " << t;
	InterpolationSmoothNotIsometry(xx, yy, k, t, ss);
	cout << "\tf(x) = " << ss[4] << endl;
    cout<<" s0 = "<<ss[0]<<"\ts1 = "<<ss[1]<<"\ts2 = "<<ss[2]<<"\ts3 = "<<ss[3]<<endl;
}
