//GammaFunction.cpp			
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
//٤����

#include <iostream>				//ģ���������������׼ͷ�ļ�
//#include <SpecialFunction.h>	//��ѧ�任ͷ�ļ�
using namespace std;			//���ֿռ�

int main(void)
{	
	double x, y;
	
	for(int i=1; i<11; i++)
    {
		x = 0.5 * i;
		y = GammaFunction(x);
		cout << "x = " << x << "\t GammaFunction(x) = " << y << endl;
	}

	cout << endl;

	y = GammaFunction(1.5) * GammaFunction(2.5) / GammaFunction(4.0);

	cout << "B(1.5,2.5) = " << y << endl;
}

