//EigenvalueVectorRealSymmetryJacobi.cpp  
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
//ʵ�Գ�������ֵ�����������ſɱȷ�

#include <iostream>				//���������ͷ�ļ�
//#include "Matrix.h"				//�����༰��غ���ͷ�ļ�
//#include "EigenvalueVector.h"	//����ֵ����������ͷ�ļ�
using namespace std;			//���ֿռ�

int main()						// �������̨Ӧ�ó������ڵ�
{
	double a[3][3] = 
	{
		{ 2.0, -1.0,  0.0},
		{-1.0,  2.0, -1.0},
		{ 0.0, -1.0,  2.0}
	};
	
	matrix<double> v(3,3), da(&a[0][0],3,3);
	double eps = FLOATERROR;
	
  	cout.setf(ios::fixed);	//�������Ϊ���㷨
	cout.precision(6);		//����6λ

	int k = EigenvalueVectorRealSymmetryJacobi(da, v, eps, 100);
	if(k > 0)
	{
		cout << "MATRIX A IS: " << endl;
		MatrixLinePrint(da);
		cout << endl;

		cout << "MATRIX V IS: " << endl;
		MatrixLinePrint(v);
		cout << endl;
	}

	double dmb[3][3] = 
	{
		{  3.0, -3.0, -2.0 },
		{ -3.0,  8.0,  4.0 },
		{  -2.0, 4.0,  3.0 } 
	};

}




