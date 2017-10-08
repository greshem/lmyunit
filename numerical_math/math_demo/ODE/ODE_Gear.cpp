//ODE_Gear.cpp	���ָ��Է����鼪����
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
	double a(0.0), b(1.0), h(0.01), hmax(0.1);
	double hmin[4]={0.0001,0.0001,0.00001,0.00001};
    double eps[4]={0.001,0.0001,0.0001,0.00001};
	matrix<double> z(3,30);
	valarray<double> y(3), t(30);
	
  	cout.setf(ios::fixed);	//�������Ϊ���㷨
	cout.precision(6);		//����6λ

	for(int k=0; k<4; k++)
	{
		y[0]=1.0;
		y[1]=0.0; 
		y[2]=-1.0;

		int iReValue = ODE_Gear(a,b,hmin[k],hmax,h,eps[k],y,30,t,z);
		cout << "h = " << h << endl;
		cout << "hmin = " << hmin[k] << endl;
		cout << "hmax = " << hmax << endl;
		cout << "eps = " << eps[k] << endl << endl;
		cout << "iReValue = " << iReValue << endl << endl;

		for(int i=0; i<30; i++)
		{
			cout << "t = " << t[i] << endl;
			for(int j=0; j<3; j++)
				cout << "    y(" << j << ") = " << z(j, i) << "\t";
			cout << endl;
		}
		cout << endl;
	}
}

//����΢�ַ������и������Ҷ˺���ֵ
template <class _Ty>
void FunctionValueG(_Ty t, valarray<_Ty>& y, valarray<_Ty>& d)
{
	int n = y.size();	//΢�ַ������з��̵ĸ�����Ҳ��δ֪�����ĸ���

    d[0]=-21.0*y[0]+19.0*y[1]-20.0*y[2];
    d[1]=19.0*y[0]-21.0*y[1]+20.0*y[2];
    d[2]=40.0*y[0]-40.0*y[1]-40.0*y[2];

}

//�����ſɱȾ���ĺ���
template <class _Ty>
void JacobiMatrix(_Ty t, valarray<_Ty>& y, matrix<_Ty>& p)
{ 
	  int n = y.size();	//΢�ַ������з��̵ĸ�����Ҳ��δ֪�����ĸ��� 

	  p(0,0)=-21.0; 
	  p(0,1)=19.0; 
	  p(0,2)=-20.0;
	  p(1,0)=19.0; 
	  p(1,1)=-21.0; 
	  p(1,2)=20.0;
	  p(2,0)=40.0;
	  p(2,1)=-40.0; 
	  p(2,2)=-40.0;
}

