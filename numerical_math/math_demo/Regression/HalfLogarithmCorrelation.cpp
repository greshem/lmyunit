//HalfLogarithmCorrelation.cpp	������������
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

#include <iostream>			//ģ�������������iostream��׼ͷ�ļ�
#include <valarray>			//ģ����valarray�ı�׼ͷ�ļ�
//#include <Statistic.h>		//���ݴ�����ع����ͷ�ļ�
using namespace std;		//���ֿռ�

int main(void)
{	
	long double t(10);
	valarray<long double> a(7);

	long double x[12] = 
	{
		0.96,0.94,0.92,0.90,0.88,0.86,
		0.84,0.82,0.80,0.78,0.76,0.74
	};

	long double y[12] = 
	{
		558.0,313.0,174.0,97.0,55.8,31.3,
		17.4, 9.70, 5.58, 3.13,1.74,1.00
	};
	 
	valarray<long double> xx(x, 12);
	valarray<long double> yy(y, 12);

	//HalfLogarithmCorrelation.cpp	������������
    HalfLogarithmCorrelation(xx, yy, t, a);

	printf("\n");
    printf("a=%13.7e   b=%13.7e  \n",a[1],a[0]);
    printf("\n");
    printf("q=%13.7e   s=%13.7e  \n",a[2],a[3]);
    printf("\n");
    printf("umax=%13.7e  umin=%13.7e  u=%13.7e \n",
                           a[4],a[5],a[6]);
    printf("\n");
}

