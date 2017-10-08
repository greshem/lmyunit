//ODE_RungeKuttaVariationalStep.cpp		 
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
//�䲽����������-������

#include <iostream>							//���������ͷ�ļ�
//#include "OrdinaryDifferentialEguation.h"	//��ⳣ΢�ַ���(��)ͷ�ļ�
using namespace std;						//���ֿռ�

int main(void)
{	
	double dy[2] = {0.0, 1.0}, t(0.0), h(0.1), eps(FLOATERROR);
	valarray<double> y(dy, 2);
		
  	cout.setf(ios::fixed);	//�������Ϊ���㷨
	cout.precision(6);		//����6λ

	cout << " t = " << t << "\t y[0] = " << y[0] << "\t y[1] = " << y[1] << endl;

	for(int i=1; i<11; i++)
	{
		ODE_RungeKuttaVariationalStep(t,h,y,eps);
		t = t + h;
		cout << " t = " << t << "\t y[0] = " << y[0] << "\t y[1] = " << y[1] << endl;
	}
}

//����΢�ַ������и������Ҷ˺���ֵ
template <class _Ty>
void FunctionValueRKVS(_Ty t, valarray<_Ty>& y, valarray<_Ty>& d)
{
	int n = y.size();	//΢�ַ������з��̵ĸ�����Ҳ��δ֪�����ĸ���

    d[0] = y[1];
	d[1] = -y[0]; 
}
