//ODE_GillVariationalStepInterval.cpp	
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
//ȫ����䲽�����ֻ�����

#include <iostream>							//���������ͷ�ļ�
//#include "OrdinaryDifferentialEguation.h"	//��ⳣ΢�ַ���(��)ͷ�ļ�
using namespace std;						//���ֿռ�

int main(void)
{	
	double y[3] = {0.0, 1.0, 1.0}, a(0.0), h(0.1), eps(FLOATERROR);
	valarray<double> vy(y, 3);
	matrix<double> vz(3,11);
	
  	cout.setf(ios::fixed);	//�������Ϊ���㷨
	cout.precision(6);		//����6λ

	ODE_GillVariationalStepInterval(a,h,vy,eps,11,vz);

	for(int i=0; i<11; i++)
	{
		double t = h * i;
		cout << "t = " << t << endl;
		for(int j=0; j<3; j++)
			cout << "    y(" << j << ") = " << vz(j, i) << "\t";
		cout << endl;
    }
}

//����΢�ַ������и������Ҷ˺���ֵ
template <class _Ty>
void FunctionValueGVSI(_Ty t, valarray<_Ty>& y, valarray<_Ty>& d)
{
	int n = y.size();	//΢�ַ������з��̵ĸ�����Ҳ��δ֪�����ĸ���

    d[0]=y[1];
	d[1]=-y[0]; 
	d[2]=-y[2];
}
