//FitCurveChebyshev.cpp		
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
//切比雪夫曲线拟合

#include <iostream>					//模板类输入输出流标准头文件
//#include "FittingApproximation.h"	//拟合与逼近头文件
using namespace std;				//名字空间

int main(void)
{	
	valarray<double> x(101), y(101), da(7);

	int i=0;
	for(int i=0; i<101; i++)
	{
		x[i] = -1.0 + 0.02 * i;
        y[i] = atan(x[i]);
    }

	FitCurveChebyshev(x,y,da);

	for (i=0; i<6; i++)
		cout << "da[" << i << "] = " << da[i] << endl;
	
	cout << endl << "MAX(p-f) = " << da[6] << endl;
}


