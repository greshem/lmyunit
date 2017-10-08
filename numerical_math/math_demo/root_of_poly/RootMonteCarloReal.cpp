//RootMonteCarloReal.cpp		 
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
//MonteCarlo���������Է���һ��ʵ��

#include <iostream>				//���������ͷ�ļ�
//#include "NonLinearEquation.h"	//�����Է���(��)���ͷ�ļ�
using namespace std;			//���ֿռ�

int main(void)
{
	long double x(0.5);			//�Ա���
	int m(10);
    long double eps(DOUBLEERROR), b(1);
            
	cout << "RootMonteCarloReal()" << endl << endl;

    RootMonteCarloReal(x,b,m,eps);
    cout << "x = " << x << endl << endl;
}

//*	���㺯��ֵ
template <class _Ty>
_Ty FunctionValueMCR(_Ty x)	//f(x)���Ա���Ϊʵ��
{
	_Ty y;
	
	y = exp(-x*x*x) - sin(x) / cos(x) + 800.0;
		
	return(y);
}

