//IntegralLaguerreGauss.cpp		���Ƕ�-��˹�����
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
//#include "Integral.h"			//����ͷ�ļ�
using namespace std;			//���ֿռ�

int main(void)
{	
	long double dValude; //a(2.5), b(8.4), eps(FLOATERROR);
	
	IntegralLaguerreGauss(dValude);
		
	cout << "IntegralLaguerreGauss()" << endl << endl;

	cout << "Integral Valude = " << dValude << endl;
}

// ���㱻������ֵ
template <class _Ty>
_Ty FunctionValueLagG(_Ty x)
{
	_Ty y;
	
	y = x * exp(-x);

    return(y);
}

