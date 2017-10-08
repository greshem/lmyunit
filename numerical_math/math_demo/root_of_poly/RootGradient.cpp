//RootGradient.cpp		 Gradient法求解非线性方程组一组实根
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

//#include <iomanip>
#include <iostream>				//输入输出流头文件
//#include "polynomials.h"		//多项式及连分式求值头文件
//#include "NonLinearEquation.h"	//非线性方程(组)求解头文件
using namespace std;			//名字空间

int main(void)
{	
	int js = 500, i;
    double eps = FLOATERROR, x[3] = {1.5, 6.5, -5.0};
	valarray<double> vx(x, 3);
    
    i=RootGradient(eps, vx, js);	//求根
	    
	cout << "RootGradient()" << endl << endl;

    if ((i>0)&&(i<js))
		for(i = 0; i < 3; i++)
			cout << "x(" << i << ") = " << vx[i] << endl;

	cout << endl;
}

//*	计算函数及导数值
template <class _Ty> 
_Ty FunctionValueRG(valarray<_Ty>& x, valarray<_Ty>& y)
{
	_Ty z,f1,f2,f3,df1,df2,df3;

    f1=x[0]-5.0*x[1]*x[1]+7.0*x[2]*x[2]+12.0;	//计算二维多项式f1函数值
    f2=3.0*x[0]*x[1]+x[0]*x[2]-11.0*x[0];		//计算二维多项式f2函数值
    f3=2.0*x[1]*x[2]+40.0*x[0];					//计算二维多项式f3函数值
    z=f1*f1+f2*f2+f3*f3;
    df1=1.0;							//计算二维多项式f1关于x1偏导数值
	df2=3.0*x[1]+x[2]-11.0;				//计算二维多项式f2关于x1偏导数值
	df3=40.0;							//计算二维多项式f3关于x1偏导数值
    y[0]=2.0*(f1*df1+f2*df2+f3*df3);
    df1=10.0*x[1];
	df2=3.0*x[0];
	df3=2.0*x[2];
    y[1]=2.0*(f1*df1+f2*df2+f3*df3);
    df1=14.0*x[2];
	df2=x[0];
	df3=2.0*x[1];
    y[2]=2.0*(f1*df1+f2*df2+f3*df3);
    return(z);
}
