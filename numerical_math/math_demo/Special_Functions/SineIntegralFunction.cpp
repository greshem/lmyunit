//SineIntegralFunction.cpp		
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
//正弦积分函数

#include <iostream>				//模板类输入输出流标准头文件
//#include <SpecialFunction.h>	//数学变换头文件
using namespace std;			//名字空间

int main(void)
{	
	double x, y;
	
	for(int i=0; i<10; i++)
	{
		x = 0.5 + i;
		y = SineIntegralFunction(x);
		cout << "  x = " << x << "   SineIntegralFunction(x) = " << y << endl;
	}
}


