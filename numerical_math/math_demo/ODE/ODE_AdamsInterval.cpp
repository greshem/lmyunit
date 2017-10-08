//ODE_AdamsInterval.cpp		 
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
//全区间积分阿当姆斯预报-校正法

#include <iostream>							//输入输出流头文件
//########################################################################
//#include <QzjUnit.hpp>
//#include <MLmyUnit.hpp>
#include <Baselib.hpp>
#include <gtest/gtest.h>
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
////#include "OrdinaryDifferentialEguation.h"	//求解常微分方程(组)头文件
using namespace std;						//名字空间

int main(void)
{	
	double y[3] = {0.0, 1.0, 1.0}, t(0.0), h(0.05), eps(FLOATERROR);
	valarray<double> vy(y, 3);
	matrix<double> vz(3,11);
	
  	cout.setf(ios::fixed);	//输出数据为定点法
	cout.precision(6);		//精度6位

	ODE_AdamsInterval(t,h,vy,eps,11,vz);

	for(int i=0; i<11; i++)
	{
		double t = h * i;
		cout << "t = " << t << endl;
		for(int j=0; j<3; j++)
			cout << "    y(" << j << ") = " << vz(j, i) << "\t";
		cout << endl;
    }
}

//计算微分方程组中各方程右端函数值
template <class _Ty>
void FunctionValueAI(_Ty t, valarray<_Ty>& y, valarray<_Ty>& d)
{
	int n = y.size();	//微分方程组中方程的个数，也是未知函数的个数
    
	d[0] = y[1];
	d[1] = -y[0]; 
	d[2] = -y[2];
}

