//WalshTransform.cpp	������ʲ�任
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

#include <iostream>		//ģ���������������׼ͷ�ļ�
//#include <Transform.h>	//��ѧ�任ͷ�ļ�
using namespace std;	//���ֿռ�

int main(void)
{	
	valarray<long double> p(8);
	valarray<long double> x(8);
	int i=0;
		
	for(int i=0; i<8; i++) p[i] = i + 1;

	WalshTransform(p, x);
	
	for(i=0; i<8; i++)
		cout << "x(" << i << ") = " << x[i] << endl;
	cout << endl;
}
