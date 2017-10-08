//FitCurveLeastSquares.cpp
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
//��С�����������

#include <iostream>					//ģ���������������׼ͷ�ļ�
//#include "FittingApproximation.h"	//�����ƽ�ͷ�ļ�
using namespace std;				//���ֿռ�

int main(void)
{	
	valarray<double> x(20), y(20), da(6), dt(3);

	int i=0;
	for(int i=0; i<20; i++)
	{
		x[i] = 0.1 * i;
        y[i] = x[i] - exp(-x[i]);
    }
	
	cout.setf(ios::fixed);	//�������Ϊ���㷨
	cout.precision(14);		//����14λ
	//##2010_09_26_22:39:30 add by greshem
	FitCurveLeastSquares(x,y,da,dt);

	for (i=0; i<6; i++)
		cout << "da[" << i << "] = " << da[i] << endl;
	
	cout << endl;

	for (i=0; i<3; i++)
		cout << "dt[" << i << "] = " << dt[i] << endl;
}

