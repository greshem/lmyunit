//RootHalves.cpp		���ַ��������Է���ʾ��
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
    size_t m = 6;					//����ʵ������
    size_t rootNo;					//������������ʵ������
	valarray<long double> x(6);		//��������ʵ��

	long double a = -2.0, b = 5.0, step = 0.2, eps = FLOATERROR;

    rootNo = RootHalves(a, b, step, eps, x, m);		//���
	
	cout << "The amount of root is : " << rootNo << endl << endl;

    for(size_t i = 0; i < rootNo; i++)
		cout << "x(" << i << ") = " << x[i] << endl;
}

//*	����f(x)����ֵ
template <class _Ty> 
_Ty FunctionValueRH(_Ty dx)
{
	_Ty dCoff[7] = {-20,7,-7,1,3,-5,1}, dValue;

	valarray<_Ty> vdCoff(dCoff, 7);				//����ʽϵ��
	
	dValue = PolyValueOneDim(vdCoff, 7, dx);	//�������ʽֵ

	return(dValue);
}
