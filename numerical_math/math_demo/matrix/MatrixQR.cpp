//MatrixQR.cpp  
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
//�ú�˹�ɶ���(Householder)�任��һ��m*n�׵�ʵ�������QR�ֽ�

#include <iostream>		//���������
//#include "Matrix.h"		//�����༰��غ����ȵĶ���
using namespace std;	//���ֿռ�

int main()				// �������̨Ӧ�ó������ڵ�
{
	const double dma[4][3] = 
	{
		{ 1.0,  1.0, -1.0},
		{ 2.0,  1.0,  0.0},
		{ 1.0, -1.0,  0.0},
		{-1.0,  2.0,  1.0}
	};

	matrix<double> matA(&dma[0][0], 4, 3);	//����A��
	matrix<double> matQ(4, 4);				//������Q��ľ������

	cout << "matA : " << endl;
	MatrixLinePrint(matA);					//�����������matA
	
	cout << endl << "matQ : " << endl;
	
	if(MatrixQR(matA, matQ))				//����Q����R����matA��������
	MatrixLinePrint(matQ);					//�����������matQ

	cout << endl << "matR : " << endl;
	
	MatrixLinePrint(matA);					//�����������matR
}
