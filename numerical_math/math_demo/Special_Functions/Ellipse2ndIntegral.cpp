//Ellipse2ndIntegral.cpp		
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
//�ڶ�����Բ����

#include <iostream>				//ģ���������������׼ͷ�ļ�
////#include <SpecialFunction.h>	//��ѧ�任ͷ�ļ�
using namespace std;			//���ֿռ�

int main(void)
{	
	double f, k, y;

	for(int i=0; i<11; i++)
	{
		f = i * 3.1415926 / 18.0;
		k = 0.5;
		y = Ellipse2ndIntegral(k, f);
			cout << "Ellipse2ndIntegral(" << k << "," << f 
											<< ")\t  = " << y << endl;
		k = 1.0;
		y = Ellipse2ndIntegral(k, f);
			cout << "Ellipse2ndIntegral(" << k << "," << f 
											<< ")\t  = " << y << endl;

	}
}
