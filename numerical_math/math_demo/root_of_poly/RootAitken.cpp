//RootAitken.cpp			Aitken���������Է���һ��ʵ��
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
	int js(20), k;
    long double eps = 0.0000001, x = 0;
        
	cout << "RootNewton()" << endl << endl;

    k = RootAitken(x, eps, js);

    if (k >= 0)
		cout << "k = " << k << "\t x = " << x << endl;
}

//*	���㺯��ֵ
template <class _Ty>
_Ty FunctionValueRA(_Ty dx)
{
	_Ty dCoff[3] = {6, 0, -1}, dValue;

	valarray<_Ty> vdCoff(dCoff, 3);

	dValue = PolyValueOneDim(vdCoff, 3, dx);	//�������ʽֵ
	
	return(dValue);	
}
