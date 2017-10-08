//LinearRegressionND.cpp	nԪ���Իع����
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
//#include <Matrix.h>			//ģ����Matrixͷ�ļ�
//#include <Statistic.h>		//���ݴ�����ع����ͷ�ļ�
using namespace std;		//���ֿռ�

int main(void)
{	
	valarray<long double> a(4);
	valarray<long double> v(3);
	valarray<long double> dt(4);
	long double x0(192), h(2);

	int i,j;
	long double x[3][5] = 
	{
		{1.1,1.0,1.2,1.1,0.9},
        {2.0,2.0,1.8,1.9,2.1},
		{3.2,3.2,3.0,2.9,2.9}
	};
	
	long double y[5] = {10.1,10.2,10.0,10.1,10.0};
	 
	matrix<long double> xx(&x[0][0], 3, 5);
	valarray<long double> yy(y, 5);

    LinearRegressionND(xx,yy,a,dt,v);

	cout << endl;

	for (int i=0; i<4; i++)
		cout << " a(" << i << ") = " << a[i] << endl;
	
	cout << endl << " q = " << dt[0] << "\t s = " << dt[1];
								cout <<  "\t r = " << dt[2] << endl;
	
	cout << endl;
	
	for (i=0; i<3; i++)
		cout << " v(" << i << ") = " << v[i] << endl;

	cout << endl;

	cout << " u = " << dt[3] << endl << endl;
}

