//IntegralGaussMD.cpp	 ���ظ�˹�����
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

#include <iostream>		//���������ͷ�ļ�
//#include "Integral.h"	//����ͷ�ļ�
using namespace std;	//���ֿռ�

int main(void)
{
	long double js[3]={4,4,4}; 

	valarray<long double> vjs(js, 3);

	long double dValue = IntegralGaussMD(vjs);
	
	cout << "IntegralGaussMD()" << endl << endl;

	cout << "dValue = " << dValue << endl << endl;
}

//�����������ϡ�����ֵ
template <class _Ty>
void FunctionBoundaryGMD(int j, valarray<_Ty>& x, valarray<_Ty>& y)
{
	  switch(j)
      { 
	    case 0:	{
					y[0] = 0.0;
					y[1] = 1.0;
					break;
				}
        case 1: {
					y[0] = 0.0;
					y[1] = sqrt(1.0-x[0]*x[0]);
					break;
				}
        case 2: {
					_Ty q = x[0]*x[0]+x[1]*x[1];
					y[0] = sqrt(q);
					y[1] = sqrt(2.0-q);
					break;
                }
	  }
}

//���㱻������ֵ
template <class _Ty>
_Ty FunctionValueGMD(valarray<_Ty>& x)
{
	_Ty dValue;
	
	dValue = x[2] * x[2];

    return(dValue);
}

