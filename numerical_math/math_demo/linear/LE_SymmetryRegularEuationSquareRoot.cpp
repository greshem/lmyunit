//LE_SymmetryRegularEuationSquareRoot.cpp   
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
//���Գ������������ƽ������

#include <iostream>				//���������ͷ�ļ�
//#include "LinearEquation.h"		//���Է���(��)���ͷ�ļ�

int main()
{ 
	double a[4][4] = 
	{
		{5.0,  7.0,   6.0,   5.0},
		{7.0, 10.0,   8.0,   7.0},
		{6.0,  8.0,  10.0,   9.0},
		{5.0,  7.0,   9.0,  10.0}
	};
    
	double d[4][2] = 
	{
		{23.0,  92.0},
		{32.0, 128.0},
        {33.0, 132.0},
		{31.0, 124.0}
	};
    
	matrix<double> aa(&a[0][0], 4, 4);
	matrix<double> dd(&d[0][0], 4, 2);
		
  	cout.setf(ios::fixed);	//�������Ϊ���㷨
	cout.precision(6);		//����6λ
	
	if(LE_SymmetryRegularEuationSquareRoot(aa, dd) > 0)
	{
		cout << endl;
		cout.width(22);
		cout << "Group 1";
		cout.width(16);
		cout << "Group 2" << endl << endl;

		for(int i = 0; i < 4; i ++)
		{
			cout << " x(" << i << ") = ";
			MatrixLinePrint(dd, i);
		}
	}
	cout << endl;
}

