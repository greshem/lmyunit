//RootQR.cpp					QR����ʵϵ����������ȫ����
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
//#include "NonLinearEquation.h"	//�����Է���(��)���ͷ�ļ�
using namespace std;			//���ֿռ�

int main(void)
{	
	size_t i, jt = 60, n=6;
    double eps = DOUBLEERROR;

    valarray<complex<double> > cx(6);

    double a[7] = {-30.0, 10.5, -10.5, 1.5, 4.5, -7.5, 1.5};
	valarray<double> va(a, 7);
	        
	cout << "RootQR()" << endl << endl;

	i = RootQR(va, cx, eps, jt);		//���

    if (i > 0)
		for (i=0; i<6; i++)
			cout << "cx(" << i << ") = " << cx[i] << endl;

	cout << endl;
}



