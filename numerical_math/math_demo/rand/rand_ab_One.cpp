//rand_ab_One.cpp	��������[a,b]������һ�����ȷֲ�α�������
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
	size_t a = 1000, b = 9999;
	size_t seed = time (NULL);				//ȡ����
	for(size_t st = 0; st < 40; st++)
	{
		if (st % 5 == 0) cout << endl;
		cout << rand_ab_One(a, b, seed) << "\t " ;
	}
	cout << endl;
}

