//IntegralHermiteGauss.cpp	 ��������-��˹�����
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
	long double dValue;
	
	cout << "IntegralHermiteGauss()" << endl << endl;

	IntegralHermiteGauss(dValue);

	cout << "dValue = " << dValue << endl << endl;
}

// ���㱻������ֵ
template <class _Ty>
_Ty FunctionValueHG(_Ty x)
{
	_Ty dValue;
	
	dValue = x * x * exp(-x * x);

    return(dValue);
}



