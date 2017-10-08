//PolyValueOneDim.cpp		一维实(复)多项式求值示例
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

//求多项式p(x)=2x^6-5x^5+3x^4+x^3-7x^2+7x-20
//在x=-0.9,0.9,-1.1,1.1,-1.3,1.3处的函数值
int main(void)
{
	cout << "PolyValueOneDim()" << endl << endl;

	//多项式系数与自变量都为实数
	cout << "Coefficient and variable are real. Result is real: " << endl;
	double dCoff[7] = {-20.0, 7.0, -7.0, 1.0, 3.0, -5.0, 2.0};
	double x[6] = {0.9, -0.9, 1.1, -1.1, 1.3, -1.3};

	valarray<double> vCoff(dCoff,7);
	
	cout.setf(ios::fixed|ios::left);	//输出数据为定点法，靠左对齐
	cout.precision(6);					//精度6位
	
	size_t st;
	for(size_t st = 0; st < 6; st++)	//输出多项式值
	{
		double dValue = PolyValueOneDim(vCoff, 7, x[st]);
		cout << "x(" << st << ") = " << x[st];
		cout << "\t p(" << st << ") = "	<< dValue << endl;
	}

	cout << endl;

	//多项式系数与自变量都为复数
	cout << "Coefficient and variable are complex. Result is complex: " << endl;
	complex<double> cdCoff[7] = 
	{		complex<double>(1.2, 3.4), 
			complex<double>(-3.2, -4.8),complex<double>(2.7, -6.4),
			complex<double>(3.1, 5.9), complex<double>(3.5, 3.9),
			complex<double>(12.1, -5.4), complex<double>(-2.5, 8.4),
	};
	
	complex<double> cx[6] = 
	{ 
			complex<double>(0.9, 1.4), complex<double>(-0.5, 1.4),
			complex<double>(-0.9, -1.8),complex<double>(-1.1, -1.4),
			complex<double>(1.1, 1.9), complex<double>(-1.5, 1.9),
	};
	
	valarray<complex<double> > vcdCoff(cdCoff,7);

	for(st = 0; st < 6; st++)	//输出多项式值
	{
		complex<double> cp = PolyValueOneDim(vcdCoff, 7, cx[st]);
		cout << "cx(" << st << ") = " << cx[st];
		cout << "\t cp(" << st << ") = " << cp << endl;
	}
	cout << endl;

	//多项式系数为实数，自变量为复数
	cout << "Coefficient is real. Variable is complex. Result is complex: " << endl;
	double drCoff[7] = {1,2,3,4,5,6,7};
	valarray<double> vdrCoff(drCoff,7);

	for(st = 0; st < 6; st++)	//输出多项式值
	{
		complex<double> dp = PolyValueOneDim(vdrCoff, 7, cx[st]);
		cout << "cx(" << st << ") = " << cx[st];
		cout << "\t dp(" << st << ") = " << dp << endl;
	}
	cout << endl;
}

