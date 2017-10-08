//ODE_Gear.cpp	积分刚性方程组吉尔法
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

#include <iostream>							//输入输出流头文件
//#include "OrdinaryDifferentialEguation.h"	//求解常微分方程(组)头文件
using namespace std;						//名字空间


int main(void)
{	
	double a(0.0), b(1.0), h(0.01), hmax(0.1);
	double hmin[4]={0.0001,0.0001,0.00001,0.00001};
    double eps[4]={0.001,0.0001,0.0001,0.00001};
	matrix<double> z(3,30);
	valarray<double> y(3), t(30);
	
  	cout.setf(ios::fixed);	//输出数据为定点法
	cout.precision(6);		//精度6位

	for(int k=0; k<4; k++)
	{
		y[0]=1.0;
		y[1]=0.0; 
		y[2]=-1.0;

		int iReValue = ODE_Gear(a,b,hmin[k],hmax,h,eps[k],y,30,t,z);
		cout << "h = " << h << endl;
		cout << "hmin = " << hmin[k] << endl;
		cout << "hmax = " << hmax << endl;
		cout << "eps = " << eps[k] << endl << endl;
		cout << "iReValue = " << iReValue << endl << endl;

		for(int i=0; i<30; i++)
		{
			cout << "t = " << t[i] << endl;
			for(int j=0; j<3; j++)
				cout << "    y(" << j << ") = " << z(j, i) << "\t";
			cout << endl;
		}
		cout << endl;
	}
}

//计算微分方程组中各方程右端函数值
template <class _Ty>
void FunctionValueG(_Ty t, valarray<_Ty>& y, valarray<_Ty>& d)
{
	int n = y.size();	//微分方程组中方程的个数，也是未知函数的个数

    d[0]=-21.0*y[0]+19.0*y[1]-20.0*y[2];
    d[1]=19.0*y[0]-21.0*y[1]+20.0*y[2];
    d[2]=40.0*y[0]-40.0*y[1]-40.0*y[2];

}

//计算雅可比矩阵的函数
template <class _Ty>
void JacobiMatrix(_Ty t, valarray<_Ty>& y, matrix<_Ty>& p)
{ 
	  int n = y.size();	//微分方程组中方程的个数，也是未知函数的个数 

	  p(0,0)=-21.0; 
	  p(0,1)=19.0; 
	  p(0,2)=-20.0;
	  p(1,0)=19.0; 
	  p(1,1)=-21.0; 
	  p(1,2)=20.0;
	  p(2,0)=40.0;
	  p(2,1)=-40.0; 
	  p(2,2)=-40.0;
}

