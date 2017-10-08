//EigenvalueVectorRealSymmetryJacobiB.cpp  
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
//ʵ�Գ�������ֵ�����������ſɱȹ��ط�

#include <iostream>				//���������ͷ�ļ�
//#include "Matrix.h"				//�����༰��غ���ͷ�ļ�
//#include "EigenvalueVector.h"	//����ֵ����������ͷ�ļ�
using namespace std;			//���ֿռ�

int main()						// �������̨Ӧ�ó������ڵ�
{
	double a[5][5] = 
	{	
		{10.0,  1.0,  2.0,  3.0,  4.0},
        { 1.0,  9.0, -1.0,  2.0, -3.0},
        { 2.0, -1.0,  7.0,  3.0, -5.0},
        { 3.0,  2.0,  3.0, 12.0, -1.0},
		{ 4.0, -3.0, -5.0, -1.0, 15.0} 
	};

	matrix<double> v(5,5), da(&a[0][0],5,5);
	double eps = FLOATERROR;
	
  	cout.setf(ios::fixed);	//�������Ϊ���㷨
	cout.precision(6);		//����6λ

	if(EigenvalueVectorRealSymmetryJacobiB(da,v,eps)>0)
	{
		cout << "MATRIX A IS: " << endl;
		MatrixLinePrint(da);
		cout << endl;

		cout << "MATRIX V IS: " << endl;
		MatrixLinePrint(v);
		cout << endl;
	}
}

