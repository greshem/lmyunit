//RootGradient.cpp		 Gradient���������Է�����һ��ʵ��
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

//#include <iomanip>
#include <iostream>				//���������ͷ�ļ�
//#include "polynomials.h"		//����ʽ������ʽ��ֵͷ�ļ�
//#include "NonLinearEquation.h"	//�����Է���(��)���ͷ�ļ�
using namespace std;			//���ֿռ�

int main(void)
{	
	int js = 500, i;
    double eps = FLOATERROR, x[3] = {1.5, 6.5, -5.0};
	valarray<double> vx(x, 3);
    
    i=RootGradient(eps, vx, js);	//���
	    
	cout << "RootGradient()" << endl << endl;

    if ((i>0)&&(i<js))
		for(i = 0; i < 3; i++)
			cout << "x(" << i << ") = " << vx[i] << endl;

	cout << endl;
}

//*	���㺯��������ֵ
template <class _Ty> 
_Ty FunctionValueRG(valarray<_Ty>& x, valarray<_Ty>& y)
{
	_Ty z,f1,f2,f3,df1,df2,df3;

    f1=x[0]-5.0*x[1]*x[1]+7.0*x[2]*x[2]+12.0;	//�����ά����ʽf1����ֵ
    f2=3.0*x[0]*x[1]+x[0]*x[2]-11.0*x[0];		//�����ά����ʽf2����ֵ
    f3=2.0*x[1]*x[2]+40.0*x[0];					//�����ά����ʽf3����ֵ
    z=f1*f1+f2*f2+f3*f3;
    df1=1.0;							//�����ά����ʽf1����x1ƫ����ֵ
	df2=3.0*x[1]+x[2]-11.0;				//�����ά����ʽf2����x1ƫ����ֵ
	df3=40.0;							//�����ά����ʽf3����x1ƫ����ֵ
    y[0]=2.0*(f1*df1+f2*df2+f3*df3);
    df1=10.0*x[1];
	df2=3.0*x[0];
	df3=2.0*x[2];
    y[1]=2.0*(f1*df1+f2*df2+f3*df3);
    df1=14.0*x[2];
	df2=x[0];
	df3=2.0*x[1];
    y[2]=2.0*(f1*df1+f2*df2+f3*df3);
    return(z);
}
