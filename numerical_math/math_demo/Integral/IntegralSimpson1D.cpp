//IntegralSimpson1D.cpp		 �䲽�������������
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
                
	cout << "IntegralSimpson1D()" << endl << endl;

	double t = IntegralSimpson1D(a, b, eps);

	cout << "t = " << t << endl << endl;
}

// ���㱻������ֵ
template <class _Ty>
_Ty FunctionValueIS1D(_Ty x)
{
	_Ty y;

	y = log(1.0 + x) / (1.0 + x * x);
    
	return(y);
}


