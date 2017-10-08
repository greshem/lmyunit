//Interpolation3Spooling3thBoundary.cpp  
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
//第三种边界条件的三次样条函数插值，微商，积分 

//#include <iostream.h>		//输入输出流头文件
//#include "Interpolation.h"	//插值头文件

int main()
{
	int m(36), n(37), j(0);
	int i=0;
	double u, s;

	double x[37], y[37], t[36];
    
	for(int i=0; i<37; i ++)
	{
		x[i] = i * 6.2831852 / 36.0;
		y[i] = sin(x[i]);	
	}
	
	for(i=0; i<36; i++)
	{
		t[i] = (0.5 + i) *  6.2831852 / 36.0;
	}

	valarray<double> yy(y, 37);
	valarray<double> dyy(37);
	valarray<double> ddyy(37);
	valarray<double> zz(36);
	valarray<double> dzz(36);
	valarray<double> ddzz(36);
    valarray<double> tt(t, 36);
	valarray<double> xx(x, 37);
	
	s =Interpolation3Spooling3thBoundary(xx, yy, dyy, ddyy, tt, zz, dzz, ddzz);

	cout << "Interpolation3Spooling3thBoundary()" << endl << endl;
	
	cout<<"x(i)        y(i)=sin(x)            dy(i)=cos(x)           ddy(i)=-sin(x)"<<endl;
	cout<<endl<<x[0]<<"\t\t"<<yy[0]<<"\t\t"<<dyy[0]<<"\t\t"<<ddyy[0];
	
	for(i=0; i<=35; i++) 
	{
		u = t[i] * 36.0 / 0.62831852;
		cout<<endl<<u<<"\t\t"<<zz[i]<<"\t\t"<<dzz[i]<<"\t\t"<<ddzz[i];
		
		u = x[i+1] * 36.0 / 0.62831852;
		j++;
		cout<<endl<<u<<"\t\t"<<yy[j]<<"\t\t"<<dyy[j]<<"\t\t"<<ddyy[j];
	}

	cout << endl << endl << "s = " << s << endl << endl;

}


