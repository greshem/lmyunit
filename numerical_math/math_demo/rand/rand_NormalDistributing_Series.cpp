//rand_NormalDistributing_Series.cpp ���������ֵ�뷽�����̬�ֲ����������
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

//����40����ֵ�뷽�����̬�ֲ������
int main(void)
{	
	double mu = 1.0, ro = 1.5;
	valarray<double> rip(40);
	size_t stCount=40;

	double seed = (double)time(NULL);	//ȡ����

	cout.setf(ios::fixed|ios::left);	//�������Ϊ���㷨���������
	cout.precision(6);					//����6λ
	
	//���������
	rand_NormalDistributing_Series(mu, ro, seed, rip, stCount);	

	ValarrayPrint(rip);					//�������ʾ��

	cout << endl;
}

