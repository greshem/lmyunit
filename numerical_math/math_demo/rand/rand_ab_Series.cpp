//rand_ab_Series.cpp	��������[a,b]�����ھ��ȷֲ�α�����������
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

//��[1000,9999]�в���40���������
int main(void)
{	
	size_t a = 1000, b = 9999,  stCount=40;
	valarray<size_t> rip(40);
	size_t seed = time (NULL);					//ȡ����
	
	rand_ab_Series(a, b, seed, rip, stCount);	//���������

	ValarrayPrint(rip);							//�������ʾ��

	cout << endl;
}

