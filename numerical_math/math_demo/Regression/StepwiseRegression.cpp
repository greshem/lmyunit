//StepwiseRegression.cpp	逐步回归分析
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

#include <iostream>			//模板类输入输出流iostream标准头文件
#include <valarray>			//模板类valarray的标准头文件
//#include <Statistic.h>		//数据处理与回归分析头文件
//#include <Matrix.h>			//模板类Matrix头文件
using namespace std;		//名字空间

int main(void)
{	
	valarray<long double> dt(2),xx(5),b(5),v(5),s(5),ye(13),yr(13);
	long double eps = LONGDOUBLEERROR;
	matrix<long double> r(5,5);
	int i=0;
	
	long double x[13][5] = 
	{ 
		{7.0,26.0,6.0,60.0,78.5}, {1.0,29.0,15.0,52.0,74.3},
        {11.0,56.0,8.0,20.0,104.3}, {11.0,31.0,8.0,47.0,87.6},
        {7.0,52.0,6.0,33.0,95.9}, {11.0,55.0,9.0,22.0,109.2},
		{3.0,71.0,17.0,6.0,102.7}, {1.0,31.0,22.0,44.0,72.5},
		{2.0,54.0,18.0,22.0,93.1}, {21.0,47.0,4.0,26.0,115.9},
		{1.0,40.0,23.0,34.0,83.8}, {11.0,66.0,9.0,12.0,113.3},
        {10.0,68.0,8.0,12.0,109.4}
	};
	
	matrix<long double> xx2(&x[0][0],13,5);
	
	long double f1[3]={1.46,4.75,9.33};
	long double f2[3]={1.45,4.67,9.07};

	for(int k=0; k<3; k++)
	{
		StepwiseRegression(xx2,f1[k],f2[k],eps,xx,b,v,s,dt,ye,yr,r);

		printf("\n");
        printf("f1=%e  f2=%e\n",f1[k],f2[k]);
        printf("\n");
        printf("original x(i) and y values:\n");
        for(int i=0; i<13; i++)
        {
			for(int j=0; j<=3; j++)	printf("x(%d)=%6.2f ",j,x[i][j]);
            printf("y=%6.2f\n",x[i][4]);
        }
        printf("\n");
        printf("mean of x(i) and y:\n");
        for(i=0; i<4; i++)
          printf("x(%d)=%6.3f ",i,xx[i]);
        printf("y=%6.3f\n",xx[4]);
        printf("\n");
        printf("regression coeffi b(i):\n");
        for(i=0; i<=4; i++)
          printf("b(%d)=%9.6f ",i,b[i]);
        printf("\n\n");
        printf("standard partial sum of square of \n");
        printf("regression for x(i) and sum of \n");
        printf("square of residuals:\n");
        for(i=0; i<4; i++)
          printf("v(%d)=%e ",i,v[i]);
        printf("\n");
        printf("q=%e\n",v[4]);
        printf("\n");
        printf("standard deviation of regression  \n");
        printf("coeffi and regression equation:\n");
        for(i=0; i<4; i++)
          printf("s(%d)=%e ",i,s[i]);
        printf("\n");
        printf("s=%e\n",s[4]);
        printf("\n");
        printf("multi-correlation coeffi c is:%e\n",dt[0]);
        printf("\n");
        printf("the f value=%e\n",dt[1]);
        printf("\n");
        printf("estimated values and residuals:\n");
        for(i=0; i<13; i++)
          printf("ye(%d)=%e  yr(%d)=%e\n",
                  i,ye[i],i,yr[i]);
        printf("\n");
        printf("matrix r:\n");
        for(i=0; i<5; i++)
        {
			for(int j=0; j<5; j++)   printf("%e  ",r(i,j));
            printf("\n");
        }
        printf("\n");
    }
}

