//Interpolation2Variable3Points.cpp  
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
//二元三点插值 

//#include <iostream.h>		//输入输出流头文件
//#include "Interpolation.h"	//插值头文件

int main()
{
	int  i, j;
	double u, v, w;

	valarray<double> x(6), y(5);
    
	for(i=0; i<6; i++) x[i] = 0.2 * i;
	for(i=0; i<5; i++) y[i] = 0.25 * i;
	
	matrix<double> z(6,5);

	for(i = 0; i < 6; i ++)
		for(j = 0; j < 5; j ++)
		{
			z(i,j) = exp( -(x[i] - y[j]) );
		}
		
	
	
	cout << "Interpolation2Variable3Points()" << endl << endl;
	
	u = 0.90;
	v = 0.80;
	w = Interpolation2Variable3Points(x, y, z, u, v);
    cout << "x = 0.9    	y = 0.8          z(x,y) = " << w << endl;
		
	u = 0.3;
	v = 0.9;
	w = Interpolation2Variable3Points(x, y, z, u, v);
    cout << "x = 0.3    	y = 0.9          z(x,y) = " << w << endl;	
}


