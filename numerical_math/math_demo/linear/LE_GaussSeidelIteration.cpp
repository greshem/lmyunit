//LE_GaussSeidelIteration.cpp	��˹-���¶������� 
//#2010_09_25_19:59:00 add by greshem
//��Ӿ���˷���֤��
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
    double eps;
    
	double a[4][4] = 
	{
		{7.0,  2.0,  1.0,  -2.0},
		{9.0,  15.0, 3.0,  -2.0},
		{-2.0, -2.0, 11.0,  5.0},
		{1.0,  3.0,  2.0,  13.0}
	};
    
	double b[4] = {4.0, 7.0, -1.0, 0.0};
	double equal[4]={};
   	valarray<double> xx(5);
	valarray<double> bb(b, 4);
	matrix<double> aa(&a[0][0], 4, 4);
	
	eps = FLOATERROR;
	
  	cout.setf(ios::fixed);	//�������Ϊ���㷨
	cout.precision(6);		//����6λ
    
	if(LE_GaussSeidelIteration(aa, bb, xx, eps) > 0)
	{
		for(i = 0; i < 4; i ++)
        {
			cout << "x(" << i << ") = " << xx[i] << endl;
			equal[i]=xx[i];
		}
		matrix<double> matA(&a[0][0], 4, 4);
		matrix<double> matB(&xx[0], 4, 1);
		MatrixLinePrint(matA*matB);	
	}
	cout << endl;
}

