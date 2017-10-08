//LE_TotalChoiceGauss.cpp	全选主元高斯消去法
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

#include <iostream>			//输入输出流头文件
//#include "LinearEquation.h"	//线性方程(组)求解头文件

int main()
{
	int i;
	double a[4][4] =		//实系数矩阵
    {
			 {0.2368, 0.2471, 0.2568, 1.2671},
             {0.1968, 0.2071, 1.2168, 0.2271},
             {0.1581, 1.1675, 0.1768, 0.1871},
             {1.1161, 0.1254, 0.1397, 0.1490} 
	};
    
	double b[4] = {1.8471, 1.7471, 1.6471, 1.5471};
    
	matrix<double> aa(&a[0][0], 4, 4);
	valarray<double> bb(b,4);
	
  	cout.setf(ios::fixed);	//输出数据为定点法
	cout.precision(6);		//精度6位
    
	if(LE_TotalChoiceGauss(aa, bb) != 0)
	{
		for(i = 0; i < 4; i++)		//输出实数解
		{
			cout << "x(" << i << ") = ";
			ValarrayPrint(bb, i);
		}
	}
	cout<<endl;

	complex<double> ca[4][4] = 		//复系数矩阵
	{
		{complex<double>(1.0,3.0), complex<double>(3.0,-2.0),
			complex<double>(2.0,1.0), complex<double>(13.0,6.0)},
		{complex<double>(7.0,-2.0), complex<double>(2.0,7.0),
			complex<double>(1.0,5.0), complex<double>(-2.0,8.0)},
		{complex<double>(9.0,9.0), complex<double>(15.0,-3.0),
			complex<double>(3.0,15.0), complex<double>(-2.0,1.0)},
		{complex<double>(-2.0,-2.0), complex<double>(-2.0,-2.0),
			complex<double>(11.0,7.0), complex<double>(5.0,6.0)} 
	};

	matrix<complex<double> > mca(&ca[0][0], 4, 4);

	complex<double> cb[4] = 
	{
		complex<double>(2.0, 1.0), complex<double>(7.0,2.0),
		complex<double>(3.0,-2.0), complex<double>(9.0,3.0)
	};
	
	valarray<complex<double> > vcb(cb,4);

	if(LE_TotalChoiceGauss(mca, vcb) != 0)
	{	
		for(i = 0; i < 4; i++)		//输出复数解
		{
			cout << "cx(" << i << ") = " ;
			ValarrayPrint(vcb, i);
		}
	}
	cout << endl;
}


