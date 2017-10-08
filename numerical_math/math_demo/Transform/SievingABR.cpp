//SievingABR.cpp		a-b-r滤波
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

#include <iostream>		//模板类输入输出流标准头文件
//#include <Transform.h>	//数学变换头文件
using namespace std;	//名字空间

template <class _Ty>
void SievingABR5(valarray<_Ty>& y)
{ 
    _Ty s=65536.0, w=2053.0, v=13849.0, r=0.0;

	int n = y.size();

    for(int i=0; i<n; i++)
    {
		_Ty t=0.0;
        for(int j=0; j<12; j++)
        {
			r=w*r+v; 
			int m=r/s;
			r=r-m*s;
			t=t+r/s;
		}
        y[i]=0.5*(t-6.0);
    }
}

int main(void)
{	
	valarray<long double> x(250), y(250), z(250);
	long double	a=0.271, b=0.0285, r=0.0005, dt=0.04;

	int i=0;
	SievingABR5(y);
	for(int i=0; i<250; i++)
    {
		long double t=(i+1)*dt;
        z[i]=3.0*t*t-2.0*t+5.0;
        x[i]=z[i]+y[i];
    }
	
	SievingABR(x,dt,a,b,r,y);

    for(i=0; i<250; i=i+5)
    {
		long double t=(i+1)*dt;
	  	
		cout.setf(ios::fixed);		//输出数据为定点法
		
		cout.precision(2);			//精度2位
		cout << "    t=" << t;
		cout.precision(6);			//精度6位
		cout.width(12);				//宽度12列
		cout << "x(t)=" << x[i];
		cout.width(12);
		cout << "y(t)=" << y[i];
		cout.width(12);
		cout << "z(t)=" << z[i];
		cout << endl;
    }
	cout << endl;
}


