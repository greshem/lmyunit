//FractionValue.cpp			���㺯������ʽֵ
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

#include <iostream>			//���������ͷ�ļ�
//#include <polynomials.h>	//����ʽͷ����
using namespace std;		//���ֿռ�

int main()
{
	cout << "FractionValue()" << endl <<endl;

	double dXpara[7] = {1.0,2.0,3.0,4.0,5.0,6.0,0.0};
    double dCoff[7] = {1.0,3.0,-1.0,2.0,5.0,-8.0,11.0};
	
	valarray<double> vdXpara(dXpara,7), vdCoff(dCoff,6);

	double x=0.0, dValue;

	cout.setf(ios::fixed|ios::left);	//�������Ϊ���㷨���������
	cout.precision(6);					//����6λ

	for(size_t st=0; st<8; st++)
	{
		dValue = FractionValue(vdXpara,vdCoff,x);
		cout << "x = "<< x << "\t y = " << dValue << endl;
		x = x + 0.5;
	}
}

