//tDistributionFunction.cpp		
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
//t分布函数

#include <iostream>				//模板类输入输出流标准头文件
//#include <SpecialFunction.h>	//数学变换头文件
using namespace std;			//名字空间

int main(void)
{	
	double t, y;
	double a[2] = {-1.0, 3.0 };
    double d[2] = { 0.5, 15.0};

	for(int i=1; i<6; i++)
	{
		t = 0.5;
		y = tDistributionFunction(t, i);
			cout << " tDistributionFunction(" << t << "," << i 
											<< ")\t= " << y << endl;
		t = 5.0;
		y = tDistributionFunction(t, i);
			cout << " tDistributionFunction(" << t << "," << i 
											<< ")\t= " << y << endl;

	}
}


