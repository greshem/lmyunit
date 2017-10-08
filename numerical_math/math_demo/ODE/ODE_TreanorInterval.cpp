//ODE_TreanorInterval.cpp	ȫ������������ɷ�
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

#include <iostream>							//���������ͷ�ļ�
//#include "OrdinaryDifferentialEguation.h"	//��ⳣ΢�ַ���(��)ͷ�ļ�
using namespace std;						//���ֿռ�

int main(void)
{	
	double y[3] = {1.0, 0.0, -1.0}, t(0.0), h(0.001);
	valarray<double> vy(y, 3);
	matrix<double> vz(3,101);
	
  	cout.setf(ios::fixed);	//�������Ϊ���㷨
	cout.precision(6);		//����6λ

	ODE_TreanorInterval(t,h,vy,101,vz);

	for(int i=0; i<101; i+=10)
	{
		t = h * i;
		cout << "t = " << t << endl;
		for(int j=0; j<3; j++)
			cout << "    y(" << j << ") = " << vz(j, i) << "\t";
		cout << endl;
    }
	cout << endl;
}

//����΢�ַ������и������Ҷ˺���ֵ
template <class _Ty>
void FunctionValueTI(_Ty t, valarray<_Ty>& y, valarray<_Ty>& d)
{
	int n = y.size();	//΢�ַ������з��̵ĸ�����Ҳ��δ֪�����ĸ���

    d[0]=-21.0*y[0]+19.0*y[1]-20.0*y[2];
    d[1]=19.0*y[0]-21.0*y[1]+20.0*y[2];
    d[2]=40.0*y[0]-40.0*y[1]-40.0*y[2];
}

