//RootFraction.cpp		Fraction���������Է���һ��ʵ��
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
//#include "polynomials.h"		//����ʽ������ʽ��ֵͷ�ļ�
//#include "NonLinearEquation.h"	//�����Է���(��)���ͷ�ļ�
using namespace std;			//���ֿռ�


int main(void)
{	
    double eps = DOUBLEERROR, x = 1.0;

	cout << "RootFraction()" << endl << endl;
    
    int k = RootFraction(x, eps);

    if(k >= 0)
		cout << "k = " << k << "  x = " << x << endl;

	cout << endl;
}

//*	���㺯��ֵ
template <class _Ty>
_Ty FunctionValueRF(_Ty dx) 
{
	_Ty dCoff[4]={-1, 0, -1, 1}, dValue;

	valarray<_Ty> vdCoff(dCoff, 4);

	dValue = PolyValueOneDim(vdCoff, 4, dx);	//�������ʽֵ
	
	return(dValue);
}
