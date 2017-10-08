//Interpolation3Spooling1stBoundary.cpp  
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
//第一种边界条件的三次样条函数插值，微商，积分 

//#include <iostream.h>		//输入输出流头文件
//#include "Interpolation.h"	//插值头文件

int main()
{
	int m(8), n(12);
	double s, dy[12];
	int i=0;
	double x[12] = 
	{
		 0.52,    8.0, 17.95, 28.65, 50.65, 104.6, 
		156.6, 	260.7, 364.4, 468.0, 507.0, 520.0
	};
	
	double y[12] = 
	{
		5.28794, 13.84, 20.2, 24.9, 31.1, 36.5, 
		   36.6,  31.0, 20.9,  7.8,  1.5,  0.2
	};
	
	double t[8] = 
	{
		4.0, 14.0, 30.0, 60.0, 130.0, 230.0, 450.0, 515.0
	};

	dy[0] = 1.86548;
	dy[11] = -0.046115;

	valarray<double> xx(x, 12);
	valarray<double> yy(y, 12);
	valarray<double> dyy(dy, 12);
	valarray<double> ddyy(12);
	valarray<double> tt(t, 8);
	valarray<double> zz(8);
	valarray<double> dzz(8);
	valarray<double> ddzz(8);

	cout << "Interpolation3Spooling1stBoundary()" << endl << endl;

	s = Interpolation3Spooling1stBoundary(xx, yy, dyy, ddyy, tt, zz, dzz, ddzz);
	
    cout << "x(i)            y(i)               dy(i)                   ddy(i)"<<endl;
	for(int i=0; i<12; i++) 
		cout<<endl<<xx[i]<<"\t\t"<<yy[i]<<"\t\t"<<dyy[i]<<"\t\t"<<ddyy[i];

	cout << endl << endl << "s = " << s << endl << endl;

	cout<<"t(i)            z(i)               dz(i)                   ddz(i)"<<endl;
    for(i=0; i<8; i++) 
		cout<<endl<<tt[i]<<"\t\t"<<zz[i]<<"\t\t"<<dzz[i]<<"\t\t"<<ddzz[i];

	cout << endl;
}


