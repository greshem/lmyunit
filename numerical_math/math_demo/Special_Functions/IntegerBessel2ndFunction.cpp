//IntegerBessel2ndFunction.cpp	
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
//�ڶ��������ױ���������

#include <iostream>				//ģ���������������׼ͷ�ļ�
//#include <SpecialFunction.h>	//��ѧ�任ͷ�ļ�
using namespace std;			//���ֿռ�

int main(void)
{	
	double x, y;
	
	for(int n=0; n<6; n++)
	{
		x = 0.05;
		for(int j=1; j<5; j++)
		{
			y = IntegerBessel2ndFunction(n, x);
			cout << "n = " << n << "  x = " << x 
					<< "\t  IntegerBessel2ndFunction(n, x) = " << y << endl;
			x = x * 10.0;
		}
	}
}
