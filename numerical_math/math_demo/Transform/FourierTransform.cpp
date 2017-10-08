//FourierTransform.cpp	快速傅里叶变换
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
	valarray< complex<long double> > p(64);
	valarray< complex<long double> > f(64);

	int i=0;
	for(int i = 0; i < 64; i++)
    {
		p[i] = complex<long double>(exp(-0.1*(i+0.5)), 0.0);
		
	}

	cout << "序列Pi(i=0,1,...,63)：" << endl;

	for(i = 0; i< 16; i++)
    {
		for(int j = 0; j < 4; j++)
			cout << "  " << p[4 * i + j] << "    ";
		cout << endl;
	}
	cout << endl;
		
  	cout.setf(ios::fixed);	//输出数据为定点法
	cout.precision(6);		//精度6位

	FourierTransform(p, f, 0, 1);
	
	cout << "Pi的傅里叶变换Fi(i=0,1,...,63)：" << endl;
	for(i = 0; i<32; i++)
    {
		for(int j = 0; j<2; j++)
			cout << "  " << f[2*i+j]<< "\t";
		cout << endl;
	}
	cout << endl;

	cout << "Pi的傅里叶变换Fi(i=0,1,...,63)的模：" << endl;
	for(i=0; i<16; i++)
    {
		for(int j=0; j<4; j++)	
			cout << "  " << p[4*i+j].real() << "\t";
		cout << endl;
	}
	cout << endl;

	cout << "Pi的傅里叶变换Fi(i=0,1,...,63)的幅角(单位为度)：" << endl;
	for(i=0; i<16; i++)
    {
		for(int j=0; j<4; j++)
			cout << "  " << p[4*i+j].imag() << "\t";
		cout << endl;
	}
	cout << endl;

	FourierTransform(f, p, 1, 1);
	
	cout << "Fi的逆傅里叶变换Pi(i=0,1,...,63)的模：" << endl;
	for(i=0; i<16; i++)
    {
		for(int j=0; j<4; j++)
			cout << "  " << f[4*i+j].real() << "\t";
		cout << endl;
	}
	cout << endl;
}

