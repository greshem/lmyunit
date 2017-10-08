//Interpolation1VariableNotIsometry.cpp	
//一元全区间不等距插值

//#include <iostream.h>		//输入输出流头文件
//#include "Interpolation.h"	//插值头文件
//########################################################################
//#include <QzjUnit.hpp>
//#include <MLmyUnit.hpp>
#include <Baselib.hpp>
#include <gtest/gtest.h>
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

int main()
{
	double t(0.63), s;
	double x[10] = 
	{
		0.10, 0.15, 0.25, 0.40, 0.50, 
		0.57, 0.70, 0.85, 0.93, 1.00
	};
	
	double y[10] = 
	{
		0.904837, 0.860708, 0.778801, 0.670320, 0.606531,
		0.565525, 0.496585, 0.427415, 0.394554, 0.367879
	};

	valarray<double> yy(y,10);
	valarray<double> xx(x,10);
   
	cout << " Interpolation1VariableNotIsometry()" << endl << endl;
    
	s = Interpolation1VariableNotIsometry(xx,yy,t);	

	cout<<" t = " << t << "\t s = "<< s << endl << endl;

}
