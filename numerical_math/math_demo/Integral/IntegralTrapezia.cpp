//IntegralTrapezia.cpp		 �䲽�����η����
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
            
	cout << "IntegralTrapezia()" << endl << endl;

	double t = IntegralTrapezia(a,b,eps);

	cout << "t = " << t << endl << endl;
}

// ���㱻������ֵ
template <class _Ty>
_Ty FunctionValueIT(_Ty x)
{
	_Ty y;

	y = exp(-x*x);

    return(y);
}



