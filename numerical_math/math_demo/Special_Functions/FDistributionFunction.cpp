//FDistributionFunction.cpp		
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
//F-分布函数

#include <iostream>				//模板类输入输出流标准头文件
//#include <SpecialFunction.h>	//数学变换头文件
using namespace std;			//名字空间

int main(void)
{	
	int n1, n2;
	double f, y;
	int n[2]={ 2,5};
    int m[2]={ 3,10};

	for(int i=0; i<2; i++)
	{
		n1=n[i];
		n2=m[i];
		f=3.5;
		y = FDistributionFunction(f,n1,n2);
			cout << " FDistributionFunction(" << f << "," << n1 
									<< "," << n2 << ")\t = " << y << endl;
		f=9.0;
		y = FDistributionFunction(f,n1,n2);
			cout << " FDistributionFunction(" << f << "," << n1 
									<< "," << n2 << ")\t = " << y << endl;

	}
}

