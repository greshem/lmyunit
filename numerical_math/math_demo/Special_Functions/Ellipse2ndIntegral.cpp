//Ellipse2ndIntegral.cpp		
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
//第二类椭圆积分

#include <iostream>				//模板类输入输出流标准头文件
////#include <SpecialFunction.h>	//数学变换头文件
using namespace std;			//名字空间

int main(void)
{	
	double f, k, y;

	for(int i=0; i<11; i++)
	{
		f = i * 3.1415926 / 18.0;
		k = 0.5;
		y = Ellipse2ndIntegral(k, f);
			cout << "Ellipse2ndIntegral(" << k << "," << f 
											<< ")\t  = " << y << endl;
		k = 1.0;
		y = Ellipse2ndIntegral(k, f);
			cout << "Ellipse2ndIntegral(" << k << "," << f 
											<< ")\t  = " << y << endl;

	}
}
