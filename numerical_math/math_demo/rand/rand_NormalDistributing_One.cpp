//rand_NormalDistributing_One.cpp	���������ֵ�뷽���һ����̬�ֲ������
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

//#include <random.h>		//����㷨ͷ�ļ�
#include <iostream>		//���������ͷ�ļ�			
#include <time.h>		//ʱ��ͷ�ļ�
using namespace std;	//���ֿռ�

int main(void)
{	
	double mu = 1.0, ro = 1.5;
	double seed = (double)time(NULL);	//ȡ����
	
	//ofstream ofs("3_6.dat");			//�����ļ�3_6.dat

	cout.setf(ios::fixed|ios::left);	//�������Ϊ���㷨���������
	cout.precision(6);					//����6λ

	for(size_t st = 0; st < 40; st++)
	{
		if (st % 5 == 0) cout << endl;
		cout << rand_NormalDistributing_One(mu, ro, seed) << "\t " ;
	}
	cout << endl;
}

