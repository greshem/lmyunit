//rand_01_One.cpp	�ֱ����10��[0, 1]������ȷֲ���α�����
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

//#include <random.h>			//����㷨ͷ�ļ�
#include <iostream>			//���������ͷ�ļ�			
#include <time.h>			//ʱ��ͷ�ļ�
//########################################################################
//#include <QzjUnit.hpp>
//#include <MLmyUnit.hpp>
// #include <Baselib.hpp>
// #include <gtest/gtest.h>
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
using namespace std;		//���ֿռ�

int main(void)
{	
	double seed = (double)time(NULL);	//ȡ����

	
	cout.setf(ios::fixed|ios::left);	//�������Ϊ���㷨���������
	cout.precision(6);					//����6λ

	for(size_t st = 0; st < 10; st++)
	{	
		double rand = rand_01_One(seed);//����[0��1]���������

		cout << " random = " << rand << endl;
	}
}

