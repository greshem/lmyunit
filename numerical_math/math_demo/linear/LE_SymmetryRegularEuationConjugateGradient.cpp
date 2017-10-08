//LE_SymmetryRegularEuationConjugateGradient.cpp  
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
//���Գ�����������Ĺ����ݶȷ�
	
#include <iostream>				//���������ͷ�ļ�
//#include "LinearEquation.h"		//���Է���(��)���ͷ�ļ�

int main()
{   
	int i;
    double eps = FLOATERROR;
    double a[4][4] = 
	{
		{5.0,  7.0,   6.0,   5.0},
		{7.0, 10.0,   8.0,   7.0},
		{6.0,  8.0,  10.0,   9.0},
		{5.0,  7.0,   9.0,  10.0}
	};

    double b[4] = {23.0, 32.0, 33.0, 31.0};
    
	valarray<double> xx(4);
	valarray<double> bb(b, 4);
	matrix<double> aa(&a[0][0], 4, 4);

    if(LE_SymmetryRegularEuationConjugateGradient(aa, bb, eps, xx) > 0)
	{
		for (i=0; i<4; i++)
		{
			cout << endl << " x(" << i << ") = " << xx[i];
		}
	}

	cout << endl;
}

