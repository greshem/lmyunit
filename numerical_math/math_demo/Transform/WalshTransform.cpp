//WalshTransform.cpp	快速沃什变换
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
	valarray<long double> p(8);
	valarray<long double> x(8);
	int i=0;
		
	for(int i=0; i<8; i++) p[i] = i + 1;

	WalshTransform(p, x);
	
	for(i=0; i<8; i++)
		cout << "x(" << i << ") = " << x[i] << endl;
	cout << endl;
}
