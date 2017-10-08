//FourierTransform.cpp	���ٸ���Ҷ�任
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
	valarray< complex<long double> > p(64);
	valarray< complex<long double> > f(64);

	int i=0;
	for(int i = 0; i < 64; i++)
    {
		p[i] = complex<long double>(exp(-0.1*(i+0.5)), 0.0);
		
	}

	cout << "����Pi(i=0,1,...,63)��" << endl;

	for(i = 0; i< 16; i++)
    {
		for(int j = 0; j < 4; j++)
			cout << "  " << p[4 * i + j] << "    ";
		cout << endl;
	}
	cout << endl;
		
  	cout.setf(ios::fixed);	//�������Ϊ���㷨
	cout.precision(6);		//����6λ

	FourierTransform(p, f, 0, 1);
	
	cout << "Pi�ĸ���Ҷ�任Fi(i=0,1,...,63)��" << endl;
	for(i = 0; i<32; i++)
    {
		for(int j = 0; j<2; j++)
			cout << "  " << f[2*i+j]<< "\t";
		cout << endl;
	}
	cout << endl;

	cout << "Pi�ĸ���Ҷ�任Fi(i=0,1,...,63)��ģ��" << endl;
	for(i=0; i<16; i++)
    {
		for(int j=0; j<4; j++)	
			cout << "  " << p[4*i+j].real() << "\t";
		cout << endl;
	}
	cout << endl;

	cout << "Pi�ĸ���Ҷ�任Fi(i=0,1,...,63)�ķ���(��λΪ��)��" << endl;
	for(i=0; i<16; i++)
    {
		for(int j=0; j<4; j++)
			cout << "  " << p[4*i+j].imag() << "\t";
		cout << endl;
	}
	cout << endl;

	FourierTransform(f, p, 1, 1);
	
	cout << "Fi���渵��Ҷ�任Pi(i=0,1,...,63)��ģ��" << endl;
	for(i=0; i<16; i++)
    {
		for(int j=0; j<4; j++)
			cout << "  " << f[4*i+j].real() << "\t";
		cout << endl;
	}
	cout << endl;
}

