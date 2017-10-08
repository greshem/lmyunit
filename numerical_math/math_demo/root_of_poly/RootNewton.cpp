//RootNewton.cpp				Newton���������Է���һ��ʵ��
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
	int js = 60, k;
    long double eps = 0.000001, x = 1.5;
    
	cout << "RootNewton()" << endl << endl;

    k = RootNewton(x,eps,js);		//���

    if(k >= 0)
		cout << "k = " << k << "  x = " << x << endl;
}

//*	���㺯��������ֵ 
template <class _Ty>
void FunctionValueRN(_Ty dx, valarray<_Ty>& y)
{
	_Ty dCoff0[4] = {-1, 0, -1, 1};
	_Ty dCoff1[3] = {0, -2, 3};

	valarray<_Ty> vdCoff0(dCoff0,4), vdCoff1(dCoff1,3);

	y[0] = PolyValueOneDim(vdCoff0, 4, dx);	//�������ʽֵ
	y[1] = PolyValueOneDim(vdCoff1, 3, dx);	//�������ʽ����ֵ
}
