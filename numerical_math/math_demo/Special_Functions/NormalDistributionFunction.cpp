//NormalDistributionFunction.cpp	
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
//��̬�ֲ�����

#include <iostream>					//ģ���������������׼ͷ�ļ�
//#include <SpecialFunction.h>		//��ѧ�任ͷ�ļ�
using namespace std;				//���ֿռ�

int main(void)
{	
	double x, y, b, c;
	double a[2]={ -1.0,3.0};
    double d[2]={ 0.5,15.0};

	
	for(int i=0; i<2; i++)
	{
		b=a[i]; 
		c=d[i]; 
		x=-10.0;
		for(int j=0; j<5; j++)
		{
			y = NormalDistributionFunction(b, c, x);
			cout << " NormalDistributionFunction(" << b << "," << c 
									<< "," << x << ")\t= " << y << endl;
			x = x + 5.0;
		}

	}
}


