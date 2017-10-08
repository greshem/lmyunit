//LogarithmCorrelation.cpp.cpp	�����������
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
//#include <Statistic.h>		//ͳ��Statisticͷ�ļ�
using namespace std;		//���ֿռ�

int main(void)
{	
	valarray<long double> a(7);

	long double x[10]={0.1,1.0,3.0,5.0,8.0,10.0,20.0,50.0,80.0,100.0};
	long double y[10]={0.1,0.9,2.5,4.0,6.3,7.8,14.8,36.0,54.0,67.0};
	 
	valarray<long double> xx(x, 10);
	valarray<long double> yy(y, 10);

    LogarithmCorrelation(xx, yy, a);

	printf("\n");
    printf("a=%13.7e   b=%13.7e  \n",a[1],a[0]);
    printf("\n");
    printf("q=%13.7e   s=%13.7e  \n",a[2],a[3]);
    printf("\n");
    printf("umax=%13.7e  umin=%13.7e  u=%13.7e \n",
                           a[4],a[5],a[6]);
    printf("\n");
}

