//IntegralSimpson2D.cpp		 ���ر䲽�������������
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

#include <iostream>			//���������ͷ�ļ�
//#include "Integral.h"		//����ͷ�ļ�
using namespace std;		//���ֿռ�

int main(void)
{	
	double eps = FLOATERROR, a(0), b(1);
	                
	cout << "IntegralSimpson2D()" << endl << endl;
    
	double dValue = IntegralSimpson2D(a,b,eps);

	cout << "dValue = " << dValue << endl << endl;
}

// �����ϡ�����y1(x)��y0(x)ֵ
template <class _Ty>
void FunctionBoundaryIS2D(_Ty x, valarray<_Ty>& y)
{
	y[0] = -sqrt(1.0 -x *x);
    y[1] = -y[0];
}

// ���㱻��f(x,y)����ֵ
template <class _Ty>
_Ty FunctionValueIS2D(_Ty x, _Ty y)
{
	_Ty zValue;

	zValue = exp(x * x + y * y);
    
	return(zValue);
}



