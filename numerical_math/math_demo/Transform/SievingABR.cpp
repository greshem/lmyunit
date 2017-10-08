//SievingABR.cpp		a-b-r�˲�
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

#include <iostream>		//ģ���������������׼ͷ�ļ�
//#include <Transform.h>	//��ѧ�任ͷ�ļ�
using namespace std;	//���ֿռ�

template <class _Ty>
void SievingABR5(valarray<_Ty>& y)
{ 
    _Ty s=65536.0, w=2053.0, v=13849.0, r=0.0;

	int n = y.size();

    for(int i=0; i<n; i++)
    {
		_Ty t=0.0;
        for(int j=0; j<12; j++)
        {
			r=w*r+v; 
			int m=r/s;
			r=r-m*s;
			t=t+r/s;
		}
        y[i]=0.5*(t-6.0);
    }
}

int main(void)
{	
	valarray<long double> x(250), y(250), z(250);
	long double	a=0.271, b=0.0285, r=0.0005, dt=0.04;

	int i=0;
	SievingABR5(y);
	for(int i=0; i<250; i++)
    {
		long double t=(i+1)*dt;
        z[i]=3.0*t*t-2.0*t+5.0;
        x[i]=z[i]+y[i];
    }
	
	SievingABR(x,dt,a,b,r,y);

    for(i=0; i<250; i=i+5)
    {
		long double t=(i+1)*dt;
	  	
		cout.setf(ios::fixed);		//�������Ϊ���㷨
		
		cout.precision(2);			//����2λ
		cout << "    t=" << t;
		cout.precision(6);			//����6λ
		cout.width(12);				//���12��
		cout << "x(t)=" << x[i];
		cout.width(12);
		cout << "y(t)=" << y[i];
		cout.width(12);
		cout << "z(t)=" << z[i];
		cout << endl;
    }
	cout << endl;
}


