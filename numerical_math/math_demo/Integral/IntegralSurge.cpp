//IntegralSurge.cpp		 ���񵴺��������
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
//#include "Integral.h"	//����ͷ�ļ�
using namespace std;	//���ֿռ�

int main(void)
{	
	double eps = FLOATERROR, a(0), b(6.2831852);
    double fa[4] = {0, 1, 0, -3};
	double fb[4] = {6.2831852, 1, -6.2831852, -3};
	int m(30);
	valarray<double> ffa(fa, 4);
	valarray<double> ffb(fb, 4);
	valarray<double> s(2);
	
	cout << "IntegralSurge()" << endl << endl;

	IntegralSurge(a, b, m, ffa, ffb, s);

	cout << "s(0) = " << s[0] << "\t s(1) = " << s[1] << endl << endl;
}


