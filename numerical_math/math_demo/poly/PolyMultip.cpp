//PolyMultip.cpp		两一维实(复)多项式相乘示例
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
//#include <polynomials.h>	//多项式头文件
using namespace std;		//名字空间
void  inter_multi();


int main()
{
	inter_multi();
	return 1;
}
int main2()
{
	cout << "PolyMultip()" << endl << endl;

	//多项式系数为实数
	cout << "Coefficients are real. Result is real: " << endl;
	
	double dCoffP[6] = {4.2, -6.1, 5.4, 2.5, -1.8, 3.6};
    double dCoffQ[4] = {2.92, 3.71, -6.45, 2.64};
    
	valarray<double> vdCoffP(dCoffP,6);
	valarray<double> vdCoffQ(dCoffQ,4);
	valarray<double> vdCoffS(9);
		
	cout.setf(ios::fixed|ios::left);	//输出数据为定点法，靠左对齐
	cout.precision(4);					//精度4位
	
	PolyMultip(vdCoffP, vdCoffQ, vdCoffS);
	size_t st;
    for (size_t st = 0; st < 9; st++)
	{
		cout << "dCoffS(" << st << ") = " << vdCoffS[st] << endl;

	}
	
	cout << endl;

	//多项式系数为复数
	cout << "Coefficients are complex. Result is complex: " << endl;
	
	complex<double> cdCoffP[7] = 
	{
		complex<double>(1.2,  3.4), 
		complex<double>(-3.2, -4.8), complex<double>( 2.7, -6.4),
		complex<double>(3.1,   5.9), complex<double>( 3.5,  3.9),
		complex<double>(12.1, -5.4), complex<double>(-2.5,  8.4),
	};

	complex<double> cdCoffQ[6] = 
	{ 
		complex<double>( 0.9,  1.4), complex<double>(-0.5,  1.4),
		complex<double>(-0.9, -1.8), complex<double>(-1.1, -1.4),
		complex<double>( 1.1,  1.9), complex<double>(-1.5,  1.9),
	};

	valarray<complex<double> > vcdCoffP(cdCoffP,7);
	valarray<complex<double> > vcdCoffQ(cdCoffQ,6);
	valarray<complex<double> > vcdCoffS(12);
	
	//complex<double> cdCoffS[12];
	
    PolyMultip(vcdCoffP, vcdCoffQ, vcdCoffS);
    for (st = 0; st < 12; st++)
	{
		cout << "cdCoffS(" << st << ") = " << vcdCoffS[st] << endl;
	
	}
	
	cout << endl;
}

void  inter_multi()
{
	int dCoffP[6] = {1,1,1,1,1,1};
    int dCoffQ[4] = {2,2,2,2};
    
	valarray<int> vdCoffP(dCoffP,6);
	valarray<int> vdCoffQ(dCoffQ,4);
	valarray<int> vdCoffS(9);
		
	cout.setf(ios::fixed|ios::left);	//输出数据为定点法，靠左对齐
	cout.precision(4);					//精度4位
	
	PolyMultip(vdCoffP, vdCoffQ, vdCoffS);
	size_t st;
    for (size_t st = 0; st < 9; st++)
	{
		cout << "dCoffS(" << st << ") = " << vdCoffS[st] << endl;

	}
	
	cout << endl;

}
