//rand_01_Series.cpp	����[0,1]�����ھ��ȷֲ�α���������
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

#include <iostream>		//���������ͷ�ļ�			
#include <time.h>		//ʱ��ͷ�ļ�
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

using namespace std;	//���ֿռ�

int main(void)
{	
	double seed = (double)time(NULL);	//ȡ����
	valarray<double> dp(40);
	size_t stNum = 40;
	
	cout.setf(ios::fixed|ios::left);	//�������Ϊ���㷨���������
	cout.precision(6);					//����6λ

	rand_01_Series(seed, dp, stNum);	//����[0,1]����40�����������
	
	ValarrayPrint(dp);					//����������ʾ��
	
	cout << endl;
}

