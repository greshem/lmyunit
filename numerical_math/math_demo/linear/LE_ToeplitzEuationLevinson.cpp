//LE_ToeplitzEuationLevinson().cpp   
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
//����в����ȷ����������ѷ���� 

#include <iostream>				//���������ͷ�ļ�
//#include "LinearEquation.h"		//���Է���(��)���ͷ�ļ�

int main()
{
	int i;
    double t[6] = {6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    double b[6] = {11.0, 9.0, 9.0, 9.0, 13.0, 17.0};
    
    valarray<double> xx(6);
	valarray<double> tt(t, 6);
	valarray<double> bb(b, 6);
		
	if (LE_ToeplitzEuationLevinson(tt, bb, xx) > 0)
		for (i = 0; i < 6; i ++)
		{
			cout << "x(" << i << ") = " << xx[i] << endl;
		}

	cout << endl;    
}

