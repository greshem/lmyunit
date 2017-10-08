//RootNewtonHillDown.cpp	
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
//牛顿下山法求解代数方程全部根(实根和复根)

#include <iostream>				//输入输出流头文件
//#include "NonLinearEquation.h"	//非线性方程(组)求解头文件
using namespace std;			//名字空间

int main(void)
{	
	int i, ii;
	
	cout << "RootNewtonHillDown()" << endl << endl;

	//验证实系数  
	valarray< complex<double> > ca(6);
	double a[7] = {-20, 7, -7, 1, 3, -5, 1};
	valarray<double> va(a, 7);
    
	cout << "Result (Algebra Equation with Real Coefficient): " << endl << endl;

    i = RootNewtonHillDown(va, ca);  
    if (i > 0)
		for(ii = 0; ii < 6; ii++)
			cout << "ca(" << ii << ") = " << ca[ii] << endl;
	
	//验证复系数	
	complex<double> ccb[6] = 
	{
		complex<double>(0.1, -100.0), complex<double>(21.33, 0.0),
		complex<double>(4.9, -19.0),  complex<double>(0.0, -0.01),
		complex<double>(3.0, 2.0),    complex<double>(1.0, 0.0)
	};
	
	valarray< complex<double> > cbb(5);

	cout << endl << "Result (Algebra Equation with Complex Coefficient): " << endl << endl;

	i = RootNewtonHillDown(ccb, cbb);
    if (ii > 0)
		for(size_t ii = 0; ii < 5; ii++)
			cout << "cb(" << ii << ") = " << cbb[ii] << endl;
}

