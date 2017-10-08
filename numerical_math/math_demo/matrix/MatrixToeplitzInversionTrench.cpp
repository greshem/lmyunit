//MatrixToeplitzInversionTrench.cpp  ������(Trench)�����в�����(Toeplitz)������
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

#include <iostream>		//���������
//#include "Matrix.h"		//�����༰��غ����ȵĶ���
using namespace std;	//���ֿռ�


int main()				// �������̨Ӧ�ó������ڵ�
{
    const double t[6] = {10.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    const double tuo[6] = { 0.0,-1.0,-2.0,-3.0,-4.0,-5.0};
	valarray<double> vt(t,6), vtuo(tuo,6);

	const double dma[6][6] = 
	{
		{10.0, 5.0, 4.0, 3.0, 2.0, 1.0},
		{-1.0,10.0, 5.0, 4.0, 3.0, 2.0},
		{-2.0,-1.0,10.0, 5.0, 4.0, 3.0},
		{-3.0,-2.0,-1.0,10.0, 5.0, 4.0},
		{-4.0,-3.0,-2.0,-1.0,10.0, 5.0},
		{-5.0,-4.0,-3.0,-2.0,-1.0,10.0}
	};

	matrix<double> matT(&dma[0][0], 6, 6);
	matrix<double> matB(matT);			//��matT��ʼ��matB

	cout << "matT : " << endl;

	MatrixLinePrint(matT);				//�����������matT
	
	cout << endl << "matB = Inversion(matT) : " << endl;

	if(MatrixToeplitzInversionTrench(vt, vtuo, matB)>0)	//����matB��matT����
	MatrixLinePrint(matB);				//�����������matB

	cout << endl << "matI = matT * matB : " << endl;

	matrix<double> matI(matT * matB);	//matT * matB�õ���λ��matI
	MatrixLinePrint(matI);				//�����������matI
}

