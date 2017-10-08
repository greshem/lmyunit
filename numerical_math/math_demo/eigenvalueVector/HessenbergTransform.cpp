//HessenbergTransform.cpp  
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
//Լ��һ��ʵ����Ϊ���겮����ĳ������Ʊ任��

#include <iostream>				//���������ͷ�ļ�
//#include "Matrix.h"				//�����༰��غ���ͷ�ļ�
//#include "EigenvalueVector.h"	//����ֵ����������ͷ�ļ�
using namespace std;			//���ֿռ�

int main()						// �������̨Ӧ�ó������ڵ�
{
	double a[5][5] = 
	{
		{  1.0,   6.0, -3.0, -1.0,  7.0},
		{  8.0, -15.0, 18.0,  5.0,  4.0},
		{ -2.0,  11.0,  9.0, 15.0, 20.0},
		{-13.0,   2.0, 21.0, 30.0, -6.0},
		{ 17.0,  22.0, -5.0,  3.0,  6.0} 
	};

	matrix<double> da(&a[0][0],5,5);

	
	cout.setf(ios::fixed);	//�������Ϊ���㷨
	cout.precision(6);		//����6λ

	int iRet = HessenbergTransform(da);

	if(iRet > 0)
	{
		cout << "MATRIX A IS: " << endl;
		MatrixLinePrint(da);
		cout << endl;
	}
}

