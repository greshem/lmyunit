//RootMonteCarloGroupReal.cpp	MonteCarlo���������Է�����һ��ʵ��
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
//#include "NonLinearEquation.h"	//�����Է���(��)���ͷ�ļ�
using namespace std;			//���ֿռ�

int main(void)
{
	size_t m(10), n(3), i;
	valarray<double> x(3);		//�Ա���
	double eps(DOUBLEERROR), b(2);
    
	x[0] = x[1] = x[2] = 0;
	        
	cout << "RootMonteCarloGroupReal()" << endl << endl;

    RootMonteCarloGroupReal(x,b,m,eps);

    for(i = 0; i < n; i++)
		cout << "x(" << i << ") = " << x[i] << endl;
}

//*	���㺯��ģ
template <class _Ty>
_Ty FunctionModule(valarray<_Ty> x)	//f(x)��ϵ�����Ա���Ϊʵ��
{
	_Ty f,f1,f2,f3;

    f1 = 3.0*x[0]+x[1]+2.0*x[2]*x[2]-3.0;
    f2 = -3.0*x[0]+5.0*x[1]*x[1]+2.0*x[0]*x[2]-1.0;
    f3 = 25.0*x[0]*x[1]+20.0*x[2]+12.0;
    f = sqrt(f1*f1+f2*f2+f3*f3);
    return(f);
}

