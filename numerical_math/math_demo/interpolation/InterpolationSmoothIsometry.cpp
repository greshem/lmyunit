//InterpolationSmoothIsometry  光滑等距插值
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

//#include <iostream.h>			//输入输出流头文件
//#include "Interpolation.h"		//插值头文件

int main()
{
	int k(-1);
	double t, x(-1.0), h(0.2);

	double y[11] = 
	{
		0.0384615, 0.0588236, 0.1, 0.2, 0.5, 
		1.0,       0.5,       0.2, 0.1, 0.0588236, 0.0384615
	};

	valarray<double> yy(y,11);
	valarray<double> ss(5);

	cout << " InterpolationSmoothIsometry()" << endl << endl;
	
	t = -0.65;
	cout << " x = " << t;
	InterpolationSmoothIsometry(x, h, yy, k, t, ss);
	cout << "\tf(x) = " << ss[4] << endl;
    cout<<" s0 = "<<ss[0]<<"\ts1 = "<<ss[1]<<"\ts2 = "<<ss[2]<<"\ts3 = "<<ss[3]<<endl;

	t = 0.25;
	cout << endl << " x = " << t;
	InterpolationSmoothIsometry(x, h, yy, k, t, ss);
	cout << "\tf(x) = " << ss[4] << endl;
    cout<<" s0 = "<<ss[0]<<"\ts1 = "<<ss[1]<<"\ts2 = "<<ss[2]<<"\ts3 = "<<ss[3]<<endl;
}


