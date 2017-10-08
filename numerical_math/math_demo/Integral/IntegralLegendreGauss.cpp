//IntegralLegendreGauss.cpp	 ���õ�-��˹�����
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
	double eps = FLOATERROR, a(2.5), b(8.4);
    
	double dValue = IntegralLegendreGauss(a, b, eps);

	cout << "IntegralLegendreGauss()" << endl << endl;

	cout << "dValue = " << dValue << endl << endl;
}

// ���㱻������ֵ
template <class _Ty>
_Ty FunctionValueLegG(_Ty x)
{
	_Ty dValue;
	
	dValue= x * x + sin(x);

    return(dValue);
}
