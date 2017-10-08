//RootQuasiNewton.cpp			��ţ�ٷ��������Է�����һ��ʵ��
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

#include <iostream>				//���������ͷ�ļ�
//#include "polynomials.h"		//����ʽ������ʽ��ֵͷ�ļ�
//#include "NonLinearEquation.h"	//�����Է���(��)���ͷ�ļ�
using namespace std;			//���ֿռ�

int main(void)
{	
	int k = 100, i;
    double eps = 0.000001, x[3] = {1.0, 1.0, 1.0}, t = 0.1, h = 0.1;
    valarray<double> vx(x, 3);
        
	cout << "RootQuasiNewton()" << endl << endl;

    i = RootQuasiNewton(eps, t, h, vx, k);		//���
	
	cout << "i = " << i << endl << endl;

	for(i = 0; i < 3; i++)
		cout << "x(" << i << ") = " << vx[i] << endl;

	cout << endl;
}

//*	���㺯��ֵ
template <class _Ty> 
void FunctionValueRSN(valarray<_Ty>& x, valarray<_Ty>& y)
{
	y[0]=x[0]*x[0]+x[1]*x[1]+x[2]*x[2]-1.0;	//�������ʽf0����ֵ
    y[1]=2.0*x[0]*x[0]+x[1]*x[1]-4.0*x[2];	//�������ʽf1����ֵ
    y[2]=3.0*x[0]*x[0]-4.0*x[1]+x[2]*x[2];	//�������ʽf2����ֵ
}
