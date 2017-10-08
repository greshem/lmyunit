//FractionValue.cpp			计算函数连分式值
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

#include <iostream>			//输入输出流头文件
//#include <polynomials.h>	//多项式头函数
using namespace std;		//名字空间

int main()
{
	cout << "FractionValue()" << endl <<endl;

	double dXpara[7] = {1.0,2.0,3.0,4.0,5.0,6.0,0.0};
    double dCoff[7] = {1.0,3.0,-1.0,2.0,5.0,-8.0,11.0};
	
	valarray<double> vdXpara(dXpara,7), vdCoff(dCoff,6);

	double x=0.0, dValue;

	cout.setf(ios::fixed|ios::left);	//输出数据为定点法，靠左对齐
	cout.precision(6);					//精度6位

	for(size_t st=0; st<8; st++)
	{
		dValue = FractionValue(vdXpara,vdCoff,x);
		cout << "x = "<< x << "\t y = " << dValue << endl;
		x = x + 0.5;
	}
}

