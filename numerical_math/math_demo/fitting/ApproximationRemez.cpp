//ApproximationRemez.cpp
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
//���һ�±ƽ�����ʽ�����ȷ�

#include <iostream>					//ģ���������������׼ͷ�ļ�
//#include "FittingApproximation.h"	//�����ƽ�ͷ�ļ�
using namespace std;				//���ֿռ�

int main(void)
{	
	valarray<double> p(5);

	double a(-1), b(1), eps(DOUBLEERROR);

	//���һ�±ƽ�����ʽ�����ȷ�
	ApproximationRemez(a,b,p,eps);

	for(int i=0; i<4; i++)
		cout << "p[" << i << "] = " << p[i] << endl;
	
	cout << endl << "MAX(p-f) = " << p[4] << endl;
}

//���㺯��ֵ
template <class _Ty>
_Ty FunctionValueAR(_Ty x)
{
	_Ty y = exp(x);
    return(y);
}


