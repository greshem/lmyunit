//ExtremumFractionND.cpp	nά��ֵ����ʽ��
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

#include <iostream>		//ģ����iostream�����������׼ͷ�ļ�
//#include "Extremum.h"	//��ֵͷ�ļ�

int main(void)
{	
	valarray<int> js(2);
	long double eps = LONGDOUBLEERROR;
	valarray<long double> x(3);

	x[0] = x[1] = 0;
	
    ExtremumFractionND(x, eps, 10, js);
	
	cout << "js[0] = " << js[0] << endl;
	cout << " x[0] = " << x[0] << endl;
	cout << " x[1] = " << x[1] << endl;
	
	if (js[1] < 0)
		cout << "MIN:  ";
    else
		cout << "MAX:  ";

	cout << "z = " << x[2] <<  endl;
}

//*	���㺯��ֵ
template <class _Ty> 
_Ty FunctionValueEFND(valarray<_Ty>& x, int j)
{
	_Ty y;

	int n = x.size()-1;		//�Ա�������

	switch(j)
    { 
		case 0: y=(x[0]-1.0)*(x[0]-10.0)+(x[1]+2.0)*(x[1]+2.0)+2.0;
                break;
        case 1: y=2.0*(x[0]-1.0);
				break;
        case 2: y=2.0*(x[1]+2.0); 
				break;
    }

    return(y);
}
