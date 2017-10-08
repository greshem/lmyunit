//IntegralSurge.cpp		 高振荡函数法求积
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

#include <iostream>		//输入输出流头文件
//#include "Integral.h"	//积分头文件
using namespace std;	//名字空间

int main(void)
{	
	double eps = FLOATERROR, a(0), b(6.2831852);
    double fa[4] = {0, 1, 0, -3};
	double fb[4] = {6.2831852, 1, -6.2831852, -3};
	int m(30);
	valarray<double> ffa(fa, 4);
	valarray<double> ffb(fb, 4);
	valarray<double> s(2);
	
	cout << "IntegralSurge()" << endl << endl;

	IntegralSurge(a, b, m, ffa, ffb, s);

	cout << "s(0) = " << s[0] << "\t s(1) = " << s[1] << endl << endl;
}


