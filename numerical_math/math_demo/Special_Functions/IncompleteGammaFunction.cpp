//IncompleteGammaFunction.cpp		
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
//����ȫ٤����

#include <iostream>				//ģ���������������׼ͷ�ļ�
//#include <SpecialFunction.h>	//��ѧ�任ͷ�ļ�
using namespace std;			//���ֿռ�

int main(void)
{	
	double a[3] = {0.5,5.0,50.0};
    double x[3] = {0.1,1.0,10.0};
	
	for(int i=0; i<3; i++)
	for(int j=0; j<3; j++)
    {
		double s = a[i];
		double t = x[j];
		double y = IncompleteGammaFunction(s, t);
		cout << " GammaFunction(" << a[i] << "," << x[j] 
											<< ")\t = " << y << endl;
	}
	cout << endl;
}

