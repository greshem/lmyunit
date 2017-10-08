//IntegralMonteCarlo2D.cpp	 �������ؿ��巨���
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
	double a[3] = {1, 1, 1};
    double b[3] = {2, 2, 2};

	valarray<double> da(a,3);
	valarray<double> db(b,3);
    
	double dValue = IntegralMonteCarlo2D(da, db);	//�����������
	    
	cout << "IntegralMonteCarlo2D()" << endl << endl;

	cout << "dValue = " << dValue << endl << endl;
}

//���㱻������ֵ
template <class _Ty>
_Ty FunctionValueMC2D(int n, valarray<_Ty>& x)		
{
	_Ty dValue(0);

	for(int i=0; i<n; i++) dValue = dValue + x[i] * x[i];

    return(dValue);
}
