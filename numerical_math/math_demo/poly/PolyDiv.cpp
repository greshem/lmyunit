//PolyDiv.cpp				һά����ʽ����ʾ��
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
//#include <polynomials.h>	//����ʽͷ�ļ�
using namespace std;		//���ֿռ�

int main()
{
	cout << "PolyDiv()" << endl << endl;

	//����ʽϵ��Ϊʵ��
	cout << "Coefficients are real. Result is real: " << endl;
	size_t st;
	double dCoffP[5] = {8.0,-5.0,-3.0,6.0,3.0};
    double dCoffQ[3] = {1.0,-1.0,2.0};

    valarray<double> vdCoffP(dCoffP,5), vdCoffQ(dCoffQ,3);
	valarray<double> vdCoffS(3), vdCoffR(2);

	cout.setf(ios::fixed|ios::left);	//�������Ϊ���㷨���������
	cout.precision(4);					//����4λ
	
    if(PolyDiv(vdCoffP, vdCoffQ, vdCoffS, vdCoffR) > 0)
	{
		for(size_t st = 0; st < 3; st++)
			cout << "dCoffS(" << st << ") = " << vdCoffS[st] << endl;
		
		cout << endl;
	
		for(st = 0; st < 2; st++)
			cout << "dCoffR(" << st << ") = " << vdCoffR[st] << endl;
	}
	
	cout << endl;

	//����ʽϵ��Ϊ����
	cout << "Coefficients are complex. Result is complex: " << endl;

	complex<double> cdCoffP[5] = 
	{
		complex<double>( 8.0,  3.0), 
		complex<double>(-5.0,  4.0), complex<double>(-3.0,  4.0),
		complex<double>( 6.0, -5.0), complex<double>( 3.0, -1.0)
	};

	complex<double> cdCoffQ[3] = 
	{
		complex<double>( 1.0,  2.0), 
		complex<double>(-1.0, -3.0), complex<double>(2.0, 2.0)
	};

	valarray<complex<double> > vcdCoffP(cdCoffP,5), vcdCoffQ(cdCoffQ,3);
	valarray<complex<double> > vcdCoffS(3), vcdCoffR(2);
	
	
    if(PolyDiv(vcdCoffP, vcdCoffQ, vcdCoffS, vcdCoffR) > 0)
	{
	    for (size_t st = 0; st < 3; st++)
			cout << "cdCoffS(" << st << ") = " << vcdCoffS[st] << endl;
	
		cout << endl;
	
		for (st = 0; st < 2; st++)
			cout << "cdCoffR(" << st << ") = " << vcdCoffR[st] << endl;
	}
	
}

