//Interpolation1Variable3PointsNotIsometry.cpp	
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
//一元三点不等距插值

//#include <iostream.h>		//输入输出流头文件
//#include "Interpolation.h"	//插值头文件

int main()
{
	double t,s;
	double x[5] = {1.615, 1.634, 1.702, 1.828, 1.921};
    double y[5] = {2.41450, 2.46459, 2.65271, 3.03035, 3.34066};
	
    valarray<double> yy(y,5);
	valarray<double> xx(x,5);
    
	cout << " Interpolation1Variable3PointsNotIsometry()" << endl << endl;
	
	t = 1.682;
	cout<<" t = " << t;
	s = Interpolation1Variable3PointsNotIsometry(xx,yy,t);
    cout << "\t s1 = " << s << endl;
    
	t = 1.813;
	cout<<" t = " << t;
	s = Interpolation1Variable3PointsNotIsometry(xx,yy,t);
    cout << "\t s2 = " << s << endl << endl;

}


