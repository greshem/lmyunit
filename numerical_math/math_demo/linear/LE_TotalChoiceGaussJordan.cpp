//LE_TotalChoiceGaussJordan.cpp	ȫѡ��Ԫ��˹-Լ����ȥ�� 
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
//#include "LinearEquation.h"		//���Է���(��)���ͷ�ļ�

int main()
{
	int i;
    double a[4][4] =			//ʵϵ������
	{
		{1.0,  3.0,  2.0,  13.0},
        {7.0,  2.0,  1.0,  -2.0},
        {9.0,  15.0, 3.0,  -2.0},
        {-2.0, -2.0, 11.0, 5.0}
	};
    
	double b[4][2] = 
	{
		{9.0,  0.0},
		{6.0,  4.0},
        {11.0, 7.0},
		{-2.0, -1.0}
	};
    
	matrix<double> aa(&a[0][0], 4, 4);
	matrix<double> bb(&b[0][0], 4, 2);
	
  	cout.setf(ios::fixed);	//�������Ϊ���㷨
	cout.precision(6);		//����6λ

	if(LE_TotalChoiceGaussJordan(aa, bb) != 0)
	{
		for(i = 0; i < 4; i++)		//���ʵ����
		{
			cout << "x(" << i << ") = ";
			MatrixLinePrint(bb, i);
		}
	}
	cout<<endl;

	complex<double> caa[4][4] = 	//��ϵ������
	{
		{complex<double>(1.0,3.0),   complex<double>(3.0,-2.0),
	     complex<double>(2.0,1.0),   complex<double>(13.0,6.0)},
		{complex<double>(7.0,-2.0),  complex<double>(2.0,7.0),
		 complex<double>(1.0,5.0),   complex<double>(-2.0,8.0)},
		{complex<double>(9.0,9.0),   complex<double>(15.0,-3.0),
		 complex<double>(3.0,15.0),  complex<double>(-2.0,1.0)},
		{complex<double>(-2.0,-2.0), complex<double>(-2.0,-2.0),
		 complex<double>(11.0,7.0),  complex<double>(5.0,6.0)} 
	};

	matrix<complex<double> > mcaa(&caa[0][0], 4, 4);

	complex<double> cbb[4][2] = 
	{
		{complex<double>(2.0, 1.0), complex<double>(-2.0, 3.0)},
		{complex<double>(7.0, 2.0), complex<double>( 3.0, 7.0)},
		{complex<double>(3.0,-2.0), complex<double>( 2.0, 9.0)},
		{complex<double>(9.0, 3.0), complex<double>( 1.0, 2.0)} 
	};
	
	matrix<complex<double> > mcbb(&cbb[0][0], 4, 2);
	

	if(LE_TotalChoiceGaussJordan(mcaa, mcbb) != 0)
	{
		for(i = 0; i < 4; i++)		//���������
		{
			cout << "cx(" << i << ") = " ;
			MatrixLinePrint(mcbb, i);
		}
	}
	cout << endl;
}

