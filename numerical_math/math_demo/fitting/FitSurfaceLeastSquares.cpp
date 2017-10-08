//FitSurfaceLeastSquares.cpp
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
//���������С�����������

#include <iostream>					//ģ���������������׼ͷ�ļ�
//#include "FittingApproximation.h"	//�����ƽ�ͷ�ļ�
using namespace std;				//���ֿռ�

int main(void)
{	
	int i, j;
	matrix<double> z(11,21), a(6,5);
	valarray<double> x(11), y(21), dt(3);

	for(i=0; i<11; i++) x[i]=0.2*i;

    for(i=0; i<21; i++) y[i]=0.1*i;
    
	for(i=0; i<11; i++)
      for(j=0; j<21; j++)
        z(i,j)=exp(x[i]*x[i]-y[j]*y[j]);

	cout.setf(ios::fixed);	//�������Ϊ���㷨
	cout.precision(6);		//����6λ

	FitSurfaceLeastSquares(x,y,z,a,dt);

	cout << "MAT A(i,j) IS: " << endl << endl;

	MatrixLinePrint(a);

	cout << endl << "\t";

	for(i=0; i<3; i++)
		cout << "dt(" << i << ") = " << dt[i] << "\t";

	cout << endl;
}

