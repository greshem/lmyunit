//ODE_EulerVariationalStep.cpp		
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
//变步长积分欧拉法

#include <iostream>							//输入输出流头文件
//#include "OrdinaryDifferentialEguation.h"	//求解常微分方程(组)头文件
using namespace std;						//名字空间

int main(void)
{	
	double y[3] = {-1.0, 0.0, 1.0}, t(0.0), h(0.01), eps(0.00001);
	valarray<double> vy(y, 3);
		
  	cout.setf(ios::fixed);	//输出数据为定点法
	cout.precision(6);		//精度6位

	cout << "t = " << t << endl;
	for(int i=0; i<3; i++)
		cout << "    y(" << i << ") = " << y[i] << "\t";
	cout << endl;
	
	for(int j=1; j<11; j++)
	{
		ODE_EulerVariationalStep(t,h,vy,eps);
		t =t + h;
		cout << "t = " << t << endl;
		for(int i=0; i<3; i++)
			cout << "    y(" << i << ") = " << vy[i] << "\t";
		cout << endl;
	}
}

template <class _Ty>
void FunctionValueEVS(_Ty t, valarray<_Ty>& y, valarray<_Ty>& d)
{
    d[0]=y[1];
	d[1]=-y[0]; 
	d[2]=-y[2];
}

