//LinearRegression1D.cpp	һԪ���Իع����
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

#include <iostream>			//ģ�������������iostream��׼ͷ�ļ�
#include <valarray>			//ģ����valarray�ı�׼ͷ�ļ�
//#include <Statistic.h>		//���ݴ�����ع����ͷ�ļ�
using namespace std;		//���ֿռ�

int main(void)
{	
	valarray<long double> a(2);
	valarray<long double> dt(6);
	long double x0(192), h(2);
	
	long double x[11] = 
	{
		0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0
	};
	
	long double y[11] = 
	{
		2.75,2.84,2.965,3.01,3.20,3.25,3.38,3.43,3.55,3.66,3.74
	};
	 
	valarray<long double> xx(x, 11);
	valarray<long double> yy(y, 11);

	//LinearRegression1D.cpp	һԪ���Իع����
    LinearRegression1D(xx, yy, a, dt);

	cout << endl << "a = " << a[1] << "\t b = " << a[0] << endl;
	cout << endl << "q = " << dt[0] << "\t s = " << dt[1];
						cout <<  "\t p = " << dt[2] << endl;
	cout << endl << "umax = " << dt[3] << "\t umin = " << dt[4];
								cout <<  "\t u = " << dt[5] << endl;
}
