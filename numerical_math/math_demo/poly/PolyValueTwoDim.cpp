//PolyValueTwoDim.cpp		二维实(复)多项式求值示例
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
//#include <polynomials.h>	//多项式及连分式头文件
using namespace std;		//名字空间

//求多项式p(x,y)在多点处的函数值
int main(void)
{	
	cout << "PolyValueTwoDim()" << endl << endl;

	//多项式系数与自变量都为实数
	cout << "Coefficient and variable are real. Result is real: " << endl;
	double dCoff[4][5] = 
	{
		{ 1.0,  2.0,  3.0,  4.0,  5.0},
		{ 6.0,  7.0,  8.0,  9.0, 10.0},
		{11.0, 12.0, 13.0, 14.0, 15.0},
		{16.0, 17.0, 18.0, 19.0, 20.0}
	};
	
	matrix<double> mdCoff(&dCoff[0][0],4,5);

	double dX = 0.6081, dY = -1.3054;
	
	cout.setf(ios::fixed|ios::left);	//输出数据为定点法，靠左对齐
	cout.precision(4);					//精度4位
	
	size_t st = 0;
	for(size_t st = 0; st < 6; st++)	//输出多项式值
	{
		double dValue = PolyValueTwoDim(mdCoff, dX, dY);
		cout << "p(" << dX << ", " << dY << ") = " << dValue << endl;
		dX = dX + 0.1101;
		dY = dY - 0.1101;
	}
	cout << endl;

	//多项式系数与自变量都为复数
	cout << "Coefficient and variable are complex. Result is complex: " << endl;
	complex<double> cdCoff[5][3] = 
	{
		{complex<double>(1.2, 3.4),complex<double>(-3.2, -4.8), complex<double>(2.7, -6.4)},
		{complex<double>(3.1, -0.9),complex<double>(-3.5, 1.9),complex<double>(2.1, -5.4)},
		{complex<double>(-2.5, 1.8),complex<double>(-2.4, 2.4),complex<double>(-1.5, 0.4)},
		{complex<double>(-2.5, 2.1),complex<double>(-2.5, 8.4),complex<double>(2.3, -1.4)},
		{complex<double>(1.1, -0.2),complex<double>(-0.4, 3.4),complex<double>(0.5, -2.4)},
	};
	
	matrix<complex<double> > mcdCoff(&cdCoff[0][0],5,3);

	complex<double> cdX = complex<double>( 0.11, -1.99);
	complex<double> cdY = complex<double>(-0.11,  1.99);
	
	for(st = 0; st < 6; st++)	//输出多项式值
	{
		complex<double> cp = PolyValueTwoDim(mcdCoff, cdX, cdY);
		cout << "cp(cdX, cdY) = cp(" << cdX << ", " << cdY << ") = " << cp << endl;
		cdX = cdX + complex<double>(0.11, 0.11);
		cdY = cdY - complex<double>(0.11, 0.11);
	}	
	cout << endl;

	//多项式系数为实数，自变量为复数
	cout << "Coefficient is real. Variable is complex. Result is complex: " << endl;
	double dcCoff[5][3] =
	{
		{ 1.0,  2.0,  3.0},
		{ 4.0,  5.0,  6.0},
		{ 7.0,  8.0,  9.0},
		{10.0, 11.0, 12.0},
		{13.0, 14.0, 15.0} 
	};

	matrix<double> mdcCoff(&dcCoff[0][0], 5,3);

	cdX = complex<double>( 0.11, -1.99);
	cdY = complex<double>(-0.11,  1.99);
		
	for(st = 0; st < 6; st++)	//输出多项式值
	{
		complex<double> dp = PolyValueTwoDim(mdcCoff, cdX, cdY);
		cout << "dp(cdX, cdY) = dp(" << cdX << ", " << cdY << ") = " << dp << endl;
		cdX = cdX + complex<double>(0.11, 0.11);
		cdY = cdY - complex<double>(0.11, 0.11);
	}
}

