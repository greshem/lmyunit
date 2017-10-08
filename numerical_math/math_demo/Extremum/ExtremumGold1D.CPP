//ExtremumGold1D.CPP	�ƽ�ָ��һά������ֵ
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

#include <iostream>		//ģ����iostream�����������׼ͷ�ļ�
#include "Extremum.h"	//��ֵͷ�ļ�
using namespace std;	//���ֿռ�

int main()
{
    double fextremum,ax,bx,cx,fa,fb,fc,tol = DOUBLEERROR;
    double xmin, b = 14.56;	
    int ret, sign = 1;
     
    cout.setf(ios::fixed|ios::left);
	cout.precision(6);
	
	cout<<"\t\t\t\tExample 1"<<endl; 
	ax = 3.15;				//��ʼ��
    bx = ax + 0.01;
	cout<<"    ax\t\tbx \t    cx\t\tfa \t   fb\t\tfc"<<endl;
	cout.width(12);	cout<<ax;
	cout.width(12);	cout<<bx<<endl;
    MinimizerInterval(ax, bx, cx, fa, fb, fc);
	cout.width(12);	cout<<ax;
	cout.width(12);	cout<<bx;
	cout.width(12);	cout<<cx;
	cout.width(12);	cout<<fa;
	cout.width(12);	cout<<fb;
	cout.width(12);	cout<<fc<<endl;
		
	fextremum = ExtremumGold1D(ax, bx, cx, sign, tol, xmin);
	cout<<"  xmin = "<<xmin<<" \t fmin = "<<fextremum<<endl;
	cout<<endl;
	
	cout<<"\t\t\t\tExample 2"<<endl;
	xmin = 0.1;
	while(1)
	{ 	 
		sign = 1;
		ax = xmin + tol;
		bx = ax + 0.01;
		cout<<"    ax\t\tbx \t   cx\t\tfa \t    fb\t\tfc"<<endl;
		cout.width(12);	cout<<ax;
		cout.width(12);	cout<<bx<<endl;
		if(ret = MinimizerInterval(ax, bx, cx, sign, b, fa, fb, fc) == 0)	break;
		
		cout.width(12);	cout<<ax;
		cout.width(12);	cout<<bx;
		cout.width(12);	cout<<cx;
		cout.width(12);	cout<<fa;
		cout.width(12);	cout<<fb;
		cout.width(12);	cout<<fc<<endl;
		
		if(bx > b) break;
		fextremum = ExtremumGold1D(ax, bx, cx, sign, tol, xmin);
		if(sign==1)
			cout<<"  xmin = "<<xmin<<" \t fmin = "<<fextremum<<endl;
		else
			cout<<"  xmax = "<<xmin<<" \t fmax = "<<fextremum<<endl;
		cout<<endl;
	}

}

// ���㺯��ֵ
template <class _Ty>
_Ty FunctionValue(_Ty x)
{
	_Ty y;

	y = x*sin(x);

    return y;
}