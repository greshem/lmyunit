// MatrixRank.cpp		��ȫѡ��Ԫ��˹��Ԫ����һ��������
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

//#include <fstream>	//�ļ���ͷ�ļ�
#include <iostream>		//���������
//#include "Matrix.h"		//�����༰��غ����ȵĶ���
using namespace std;	//���ֿռ�

int main()				// �������̨Ӧ�ó������ڵ�
{
	size_t mRank;
#include "a.cpp";
#include "b.cpp";
#include "c.cpp";


	const matrix<double> matA(&a[0][0], 10, 10);
	const matrix<double> matB(&b[0][0], 10, 10);
	const matrix<double> matC(&c[0][0], 10, 10);

	mRank = MatrixRank(matA);
	cout << endl << "The rank of matA is : " << mRank << endl;

	mRank = MatrixRank(matB);
	cout << endl << "The rank of matB is : " << mRank << endl;

	mRank = MatrixRank(matC);
	cout << endl << "The rank of matC is : " << mRank << endl;
}

