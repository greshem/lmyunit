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
//�䲽������ŷ����

#include <iostream>							//���������ͷ�ļ�
//#include "OrdinaryDifferentialEguation.h"	//��ⳣ΢�ַ���(��)ͷ�ļ�
using namespace std;						//���ֿռ�

int main(void)
{	
	double y[3] = {-1.0, 0.0, 1.0}, t(0.0), h(0.01), eps(0.00001);
	valarray<double> vy(y, 3);
		
  	cout.setf(ios::fixed);	//�������Ϊ���㷨
	cout.precision(6);		//����6λ

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

