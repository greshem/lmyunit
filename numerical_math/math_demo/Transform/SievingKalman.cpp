//SievingKalman.cpp		��ɢ�������ϵͳ�Ŀ������˲�
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
//#include <Matrix.h>		//ģ�������ͷ�ļ�
using namespace std;	//���ֿռ�

template <class _Ty>
void SievingKalman5(matrix<_Ty>& y)
{
    _Ty t, s=65536, w=2053, v=13849, r=0;

	int k = y.GetRowNum();	//�۲����еĳ���

    for(int i=0; i<k; i++)
    {
		t=0.0;
        for(int j=0; j<12; j++)
        {
			r=w*r+v;
			int m=r/s;
			r=r-m*s;
			t=t+r/s;
		}
        y(i,0)=0.5*(t-6.0);
    }
}

int main(void)
{	
//	void keklm5(int n, matrix<_Ty>& y);
	int i=0;
	long double	f[3][3] = 
	{
		{1.0,0.05,0.00125}, {0.0,1.0,0.05}, {0.0,0.0,1.0}
	};

	long double	q[3][3] = 
	{
		{0.25,0.0,0.0}, {0.0,0.25,0.0}, {0.0,0.0,0.25}
	};

	long double	r[1][1] = {0.25};
	long double	h[1][3] = {1.0,0.0,0.0};

	matrix<long double> pp(3,3), xx(200,3), yy(200,1), gg(3,1);

	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++) pp(i,j) = 0;

	for (i=0; i<200; i++)
		for (int j=0; j<3; j++) xx(i,j) = 0;

	matrix<long double> ff(&f[0][0],3,3), qq(&q[0][0],3,3);
	matrix<long double>	rr(&r[0][0],1,1), hh(&h[0][0],1,3);	

	SievingKalman5(yy);
	
    for(i=0; i<200; i++)
    {
		long double t=0.05*i;
        yy(i,0)=5.0-2.0*t+3.0*t*t+yy(i,0);
    }

	int js = SievingKalman(ff,qq,rr,hh,yy,xx,pp,gg);
	
	cout.setf(ios::fixed);	//�������Ϊ���㷨
	
	if(js!=0)
    {
		cout << endl;

        cout << "  t        s           y             ";
        cout << "x[0]           x[1]           x[2]" << endl;

        for(int i=0; i<200; i=i+5)
        {
			long double t=0.05*i;
			long double s=5.0-2.0*t+3.0*t*t;
			cout.precision(2);	//����2λ
			cout << t;
			cout.precision(6);	//����6λ
			cout.width(12);		//���12��
            cout << s;
			cout.width(12);
			cout << yy(i,0);
			cout.width(15);
			cout << xx(i,0);
			cout.width(15);
			cout << xx(i,1);
			cout.width(15);
			cout << xx(i,2);
			cout <<endl;
        }
        cout << endl;
    }
}
