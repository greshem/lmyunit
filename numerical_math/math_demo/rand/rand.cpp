// rand.cpp		C++�ṩ��rand()����
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
// �ó�������time��srand������Ϊ����������������ӣ�����10�����������Ȼ�������

//#include <random.h>		//����㷨ͷ�ļ�
#include <iostream>		//���������ͷ�ļ�			
#include <time.h>		//ʱ��ͷ�ļ�
using namespace std;	//���ֿռ�

int main( void )
{
    // �������������Ҫ������ֵʹ�õ�ǰʱ�䣬�Ա�ÿ�γ�������ʱ������ֵ������ͬ��
	srand( (size_t)time( NULL ) );

    // ���10�������
	for(size_t i = 0; i < 10; i++){
		cout.width(6);
		cout << rand() << endl;
		//ofs << rand() << endl;
	}
}

