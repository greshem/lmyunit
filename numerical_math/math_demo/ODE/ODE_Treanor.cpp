//ODE_Treanor.cpp	 ����һ�������ɷ�
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
//#include "OrdinaryDifferentialEguation.h"	///��ⳣ΢�ַ���(��)ͷ�ļ�
using namespace std;						//���ֿռ�

int main(void)
{	
	double y[3] = {1.0, 0.0, -1.0}, t(0.0), h(0.001);
	valarray<double> vy(y, 3);
	
  	cout.setf(ios::fixed);	//�������Ϊ���㷨
	cout.precision(6);		//����6λ
	int i, j;

	cout << "t = " << t << endl;

	for(int j=0; j<3; j++)
		cout << "    y(" << j << ") = " << y[j] << "\t";
	cout << endl;

	for(int i=0; i<10; i++)
	{
		ODE_Treanor(t,h,vy);
		t = t + h;
		cout << "t = " << t << endl;
		for(j=0; j<3; j++)
			cout << "    y(" << j << ") = " << vy[j] << "\t";
		cout << endl;
    }
	cout << endl;
}

//����΢�ַ������и������Ҷ˺���ֵ
template <class _Ty>
void FunctionValueT(_Ty t, valarray<_Ty>& y, valarray<_Ty>& d)
{
	int n = y.size();	//΢�ַ������з��̵ĸ�����Ҳ��δ֪�����ĸ���

    d[0]=-21.0*y[0]+19.0*y[1]-20.0*y[2];
    d[1]=19.0*y[0]-21.0*y[1]+20.0*y[2];
    d[2]=40.0*y[0]-40.0*y[1]-40.0*y[2];
}

