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
//ȫѡ��Ԫ��˹-Լ��(Gauss-Jordan)���������

#include <iostream>		//���������
//#include "Matrix.h"		//�����༰��غ����ȵĶ���
using namespace std;	

int main()				// �������̨Ӧ�ó������ڵ�
{
	const double dma[4][4] =
	{
		{0.2368,0.2471,0.2568,1.2671},
		{1.1161,0.1254,0.1397,0.1490},
		{0.1582,1.1675,0.1768,0.1871},
		{0.1968,0.2071,1.2168,0.2271} 
	};

	
	matrix<double> matA(&dma[0][0], 4, 4);
	matrix<double> matB(matA);
		
	cout << "matA : " << endl;
	MatrixLinePrint(matA);			//�����������matA

	if(MatrixInversionGS(matA)>0)	//�������溯�����ж��Ƿ�>0
	{
		cout << endl << "Inversion(matA) : " << endl;
	
		MatrixLinePrint(matA);		//�����������matA����
	
		cout << endl << "Inversion(matA) * matA : " << endl;

		matA = matA * matB;
		MatrixLinePrint(matA);		//�����������matA������ĳ˻�
	}
}
