// HouseholderTransform.cpp  
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
//Լ���Գ���Ϊ�Գ����Խ���ĺ�˹�ɶ��±任��

#include <iostream>				//���������ͷ�ļ�
//#include "Matrix.h"				//�����༰��غ���ͷ�ļ�
//#include "EigenvalueVector.h"	//����ֵ����������ͷ�ļ�
using namespace std;			//���ֿռ�

int main()						//�������̨Ӧ�ó������ڵ�
{
	double a[5][5] = 
	{	
		{10.0,  1.0,  2.0,  3.0,  4.0},
        { 1.0,  9.0, -1.0,  2.0, -3.0},
        { 2.0, -1.0,  7.0,  3.0, -5.0},
        { 3.0,  2.0,  3.0, 12.0, -1.0},
		{ 4.0, -3.0, -5.0, -1.0, 15.0} 
	};
	
	valarray<double> b(5), c(5);
	matrix<double> q(5,5), da(&a[0][0],5,5);
	
	cout.setf(ios::fixed);	//�������Ϊ���㷨
	cout.precision(6);		//����6λ
	
	if(HouseholderTransform(da,q,b,c) > 0)
	{
		cout << "MATRIX A IS: " << endl;
		MatrixLinePrint(da);
		cout << endl;

		cout << "MATRIX Q IS: " << endl;
		MatrixLinePrint(q);
		cout << endl;

		cout << "MATRIX B IS: " << endl;
		ValarrayPrint(b);
		cout << endl;

		cout << "MATRIX C IS: " << endl;
		ValarrayPrint(c);
		cout << endl;
	}
	else
		cout << "Matrix A is not symmetry." << endl;
}

