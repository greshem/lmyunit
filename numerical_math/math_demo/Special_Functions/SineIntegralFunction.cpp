//SineIntegralFunction.cpp		
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
//���һ��ֺ���

#include <iostream>				//ģ���������������׼ͷ�ļ�
//#include <SpecialFunction.h>	//��ѧ�任ͷ�ļ�
using namespace std;			//���ֿռ�

int main(void)
{	
	double x, y;
	
	for(int i=0; i<10; i++)
	{
		x = 0.5 + i;
		y = SineIntegralFunction(x);
		cout << "  x = " << x << "   SineIntegralFunction(x) = " << y << endl;
	}
}


