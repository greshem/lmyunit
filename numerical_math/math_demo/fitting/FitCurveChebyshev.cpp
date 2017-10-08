//FitCurveChebyshev.cpp		
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
//�б�ѩ���������

#include <iostream>					//ģ���������������׼ͷ�ļ�
//#include "FittingApproximation.h"	//�����ƽ�ͷ�ļ�
using namespace std;				//���ֿռ�

int main(void)
{	
	valarray<double> x(101), y(101), da(7);

	int i=0;
	for(int i=0; i<101; i++)
	{
		x[i] = -1.0 + 0.02 * i;
        y[i] = atan(x[i]);
    }

	FitCurveChebyshev(x,y,da);

	for (i=0; i<6; i++)
		cout << "da[" << i << "] = " << da[i] << endl;
	
	cout << endl << "MAX(p-f) = " << da[6] << endl;
}


