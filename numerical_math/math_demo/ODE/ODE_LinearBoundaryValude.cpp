//ODE_LinearBoundaryValude.cpp	
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
//������ȫ������ֵ�ŷ����

#include <iostream>							//���������ͷ�ļ�
//#include "OrdinaryDifferentialEguation.h"	//��ⳣ΢�ַ���(��)ͷ�ļ�
using namespace std;						//���ֿռ�

int main(void)
{	
	double a(2.0), b(3.0), ya(0.0), yb(0.0);
		//y[3] = {-1.0, 0.0, 1.0}, t(0.0), h(0.01);
	valarray<double> y(11);
	//matrix<double> vz(3,11);
	
  	cout.setf(ios::fixed);	//�������Ϊ���㷨
	cout.precision(6);		//����6λ

	ODE_LinearBoundaryValude(a,b,ya,yb,11,y);

	for(int i=0; i<11; i++)
		cout << "    y(" << i << ") = " << y[i] << endl;
	cout << endl;
}

//�������΢�ַ����麯��
template <class _Ty>
void FunctionValueLBV(_Ty x, valarray<_Ty>& z)
{
	z[0]=-1.0; 
	z[1]=0.0;
    z[2]=2.0/(x*x);
	z[3]=1.0/x;
}

