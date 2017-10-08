//RootQR.cpp					QR法求实系数代数方程全部根
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

#include <iostream>				//输入输出流头文件
//#include "NonLinearEquation.h"	//非线性方程(组)求解头文件
using namespace std;			//名字空间

int main(void)
{	
	size_t i, jt = 60, n=6;
    double eps = DOUBLEERROR;

    valarray<complex<double> > cx(6);

    double a[7] = {-30.0, 10.5, -10.5, 1.5, 4.5, -7.5, 1.5};
	valarray<double> va(a, 7);
	        
	cout << "RootQR()" << endl << endl;

	i = RootQR(va, cx, eps, jt);		//求根

    if (i > 0)
		for (i=0; i<6; i++)
			cout << "cx(" << i << ") = " << cx[i] << endl;

	cout << endl;
}



