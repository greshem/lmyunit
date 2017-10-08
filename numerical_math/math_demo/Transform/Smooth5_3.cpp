//Smooth5_3.cpp		五点三次平滑(曲线拟合)
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

#include <iostream>		//模板类输入输出流标准头文件
//#include <Transform.h>	//数学变换头文件
using namespace std;	//名字空间

int main(void)
{	
	long double y[9] = 
	{
		54.0,145.0,227.0,359.0,401.0,342.0,259.0,112.0,65.0
	};

	valarray<long double> yd(y,9);
	valarray<long double> yy(9);
		
	Smooth5_3(yd, yy);
	
	for(int i=0; i<9; i++)
		cout << "y(" << i << ") = " << y[i] 
			 << "\t yy(" << i << ") = " << yy[i] << endl;

	cout << endl;
}
