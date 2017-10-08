//ODE_GillVariationalStep.cpp	
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
//�䲽������һ��������

#include <iostream>							//���������ͷ�ļ�
//#include "OrdinaryDifferentialEguation.h"	//��ⳣ΢�ַ���(��)ͷ�ļ�
using namespace std;						//���ֿռ�

int main(void)
{	
	double q[3] = {0.0, 0.0, 0.0};
	double y[3] = {0.0, 1.0, 1.0};
	double t(0.0), h(0.1), eps(FLOATERROR);
	int i=0;
	valarray<double> vy(y, 3), vq(q, 3);
			
  	cout.setf(ios::fixed);	//�������Ϊ���㷨
	cout.precision(6);		//����6λ

	cout << "t = " << t << endl;
	for(int i=0; i<3; i++)
		cout << "    y(" << i << ") = " << y[i] << "\t";
	cout << endl;

	for(i=1; i<11; i++)
	{
		ODE_GillVariationalStep(t,h,vy,eps,vq);
		t = h * i;
		cout << "t = " << t << endl;
		for(int j=0; j<3; j++)
			cout << "    y(" << j << ") = " << vy[j] << "\t";
		cout << endl;
    }
}

//����΢�ַ������и������Ҷ˺���ֵ
template <class _Ty>
void FunctionValueGVS(_Ty t, valarray<_Ty>& y, valarray<_Ty>& d)
{
	int n = y.size();	//΢�ַ������з��̵ĸ�����Ҳ��δ֪�����ĸ���

    d[0] = y[1];
	d[1] = -y[0]; 
	d[2] = -y[2];
}
