//RootMonteCarloComplex.cpp		
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
//MonteCarlo法求解非线性方程一复根

#define FM	//注解此行，将调用FunctionModule2()

#ifdef FM
	#define FunctionModule FunctionModule1
#else 
	#define FunctionModule FunctionModule2
#endif

#include <iostream>				//输入输出流头文件
//#include "polynomials.h"		//多项式及连分式求值头文件
//#include "NonLinearEquation.h"	//非线性方程(组)求解头文件
using namespace std;			//名字空间

int main(void)
{
	int m = 10;
    double eps = FLOATERROR, b = 1;
	complex<double> cxy(0.5, 0.5);	//自变量
	        
	cout << "RootMonteCarloComplex()" << endl << endl;
    
    RootMonteCarloComplex(cxy,b,m,eps);

    cout << "z = " << cxy << endl;
}

//*	计算函数模
template <class _Tz>
double FunctionModule1(_Tz cxy)	//f(x)的自变量为复数
{
	_Tz cmodule(cxy);
	double dCoff[3] = {13, -6, 1};
	valarray<double> vdCoff(dCoff,3);
	
	cmodule = PolyValueOneDim(vdCoff, 3, cxy);


	return(Abs(cmodule));
}

//*	计算函数模
template <class _Tz>
double FunctionModule2(_Tz cxy)	//f(x)的自变量与系数都为复数
{
	_Tz cmodule(cxy);

	complex<double> cdCoff[3] = 
	{
		complex<double>(-1,2),
		complex<double>( 1,1), 
		complex<double>( 1,0)
	};

	valarray<complex<double> > vcdCoff(cdCoff,3);

	cmodule = PolyValueOneDim(vcdCoff, 3, cxy);

	return(Abs(cmodule));
}
