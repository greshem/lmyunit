//X^2DistributionFunction.cpp	X^2-�ֲ�����
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

#include <iostream>				//ģ���������������׼ͷ�ļ�
//#include <SpecialFunction.h>	//��ѧ�任ͷ�ļ�
using namespace std;			//���ֿռ�

int main(void)
{	
	double t, y;

	for(int i=1; i<6; i++)
	{
		t = 0.5;
		y = X2DistributionFunction(t, i);
			cout << " X2DistributionFunction(" << t << "," << i 
											<< ")\t= " << y << endl;
		t = 5.0;
		y = X2DistributionFunction(t, i);
			cout << " X2DistributionFunction(" << t << "," << i 
											<< ")\t= " << y << endl;

	}
}


