//IntegralFraction2D.cpp ��������ʽ�����
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

#include <iostream>		//���������ͷ�ļ�
//#include "Integral.h"	//����ͷ�ļ�
using namespace std;	//���ֿռ�

int main(void)
{
	long double eps(0.00005), a(0), b(1);

	long double dValue = IntegralFraction2D(a, b, eps);
                
	cout << "IntegralSimpson1D()" << endl << endl;

	cout << "dValue = " << dValue << endl << endl;
}

//�����ϡ�����y1(x)��y0(x)
template <class _Ty>
void FunctionBoundaryF2D(_Ty x, valarray<_Ty>& y)
{
	y[1] = sqrt(1.0 - x * x);
	y[0] = - y[1];
}

//���㱻������f(x,y)ֵ
template <class _Ty>
_Ty FunctionValueF2D(_Ty x, _Ty y)
{
	_Ty dValue;

	dValue = exp(x * x + y * y);

    return(dValue);
}

