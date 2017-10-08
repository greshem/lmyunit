//ODE_MersonVariationalStep.cpp	
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
//�䲽������Ĭɭ��

#include <iostream>							//���������ͷ�ļ�
//#include "OrdinaryDifferentialEguation.h"	//��ⳣ΢�ַ���(��)ͷ�ļ�
using namespace std;						//���ֿռ�

int main(void)
{	
	double y[2] = {0.0, 1.0}, t(0.0), h(0.1), eps(FLOATERROR);
	valarray<double> vy(y, 2);
	matrix<double> vz(2,11);
	
  	cout.setf(ios::fixed);	//�������Ϊ���㷨
	cout.precision(6);		//����6λ

	ODE_MersonVariationalStep(t,h,2,vy,eps,11,vz);

	for(int i=0; i<11; i++)
	{
		double x = h * i;
		cout << "t = " << x << endl;
		cout << "    y(0) = " << vz(0, i) << "\t   y(1) = " << vz(1, i) << endl;
    }
}

//����΢�ַ������и������Ҷ˺���ֵ
template <class _Ty>
void FunctionValueMVS(_Ty t, valarray<_Ty>& y, valarray<_Ty>& d)
{
	_Ty q;

	int n = y.size();	//΢�ַ������з��̵ĸ�����Ҳ��δ֪�����ĸ���

    q = 60.0 * (0.06 + t* (t - 0.6));
    d[0] = q * y[1];
	d[1] = -q * y[0];
}

