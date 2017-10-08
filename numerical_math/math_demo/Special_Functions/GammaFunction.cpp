//GammaFunction.cpp			
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
//伽马函数

#include <iostream>				//模板类输入输出流标准头文件
//#include <SpecialFunction.h>	//数学变换头文件
using namespace std;			//名字空间

int main(void)
{	
	double x, y;
	
	for(int i=1; i<11; i++)
    {
		x = 0.5 * i;
		y = GammaFunction(x);
		cout << "x = " << x << "\t GammaFunction(x) = " << y << endl;
	}

	cout << endl;

	y = GammaFunction(1.5) * GammaFunction(2.5) / GammaFunction(4.0);

	cout << "B(1.5,2.5) = " << y << endl;
}

