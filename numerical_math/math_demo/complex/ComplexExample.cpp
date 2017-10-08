//����ʾ��					ComplexExample.cpp
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

//########################################################################
//#include <QzjUnit.hpp>
//#include <MLmyUnit.hpp>
#include <Baselib.hpp>
#include <gtest/gtest.h>
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
#include <iostream>		//���������ͷ�ļ�
#include <complex>		//������ͷ����
#include <numerical_math.hpp>
using namespace std;	//���ֿռ�

int main()				// �������̨Ӧ�ó������ڵ�
{
	double dcr=-3.1, dci=14.5;
	complex<double> cda(dcr,dci);			//���帴������cda
	cout << " 1 cda = " << cda << endl;
	complex<double> cdb(cda);				//���帴������cdb
	cout << " 2 cdb = " << cdb << endl;
	complex<double> cdc(-2.4, 7.9);			//���帴������cda
	cout << " 3 cdc = " << cdc << endl;
	complex<int> cia(5,8);					//���帴������cia
	complex<float> cla;						//���帴������cla
	cout << " 4 cia = " << cia << "     cla = " << cla << endl;
	cia=9;									//caiʵ���鲿�ֱ�9��0
	cout << " 5 cia = " << cia << endl;
	dcr = cdc.real();						//ȡcdcʵ������
	cout << " 6 cda.real() = " << dcr << endl;
	dci = cdc.imag();						//ȡcdc��������
	cout << " 7 cda.imag() = " << dci << endl;
	cout << " 8 real(cdb) = " << real(cdb) << endl;
	cout << " 9 imag(cdb) = " << imag(cdb) << endl;
	cout << "10 (cdc = cda) = " << (cdc = cda) << endl;	
	cout << "11 (cda += cdb) = " << (cda += cdb) << endl;
	cout << "12 (cda -= cdb) = " << (cda -= cdb) << endl;
	cout << "13 (cdb *= cdc) = " << (cdb *= cdc) << endl;
	cout << "14 (cda /= cdc) = " << (cda /= cdc) << endl;
	cout << "15 (cda = cdc + cdb) =  " << (cda = cdc + cdb) << endl;
	cout << "16 (cda = cda - cdb) =  " << (cda = cda - cdb) << endl;
	cout << "17 (cda = cda * cdb) =  " << (cda = cda * cdb) << endl;
	cout << "18 (cda = cda / cdb) =  " << (cda = cda / cdb) << endl;
	cout << "19 abs(cda) = " << abs(cda) << endl;
	cout << "20 arg(cda) = " << arg(cda) << endl;
	cout << "21 conj(cna) = " << (conj(cda)) << endl;
	cout << "22 sin(cda) = " << sin(cda) << endl;
	cout << "23 cos(cda) = " << cos(cda) << endl;
	cout << "24 sinh(cda) = " << sinh(cda) << endl;
	cout << "25 cosh(cda) = " << cosh(cda) << endl;
	cout << "26 exp(cda) = " << exp(cda) << endl;
	cout << "27 log(cda) = " << log(cda) << endl;
	cout << "28 log10(cda) = " << log10(cda) << endl;
	cout << "29 norm(cda) = " << norm(cda) << endl;
	cout << "30 polar(dcr, dci) = " << polar(dcr, dci) << endl;
	cout << "31 pow(cdc, 3) = " << pow(cdc, 3) << endl;
	cout << "32 sqrt(cdc) = " << sqrt(cdc) << endl;
	cout << "33 (cdc == cdb) = " << (cdc==cdb) << endl;
	cout << "34 (cdc != cdb) = " << (cdc!=cdb) << endl;
	cout << "35 pow(cdb, cda) = " << pow(cdb, cda) << endl;
}
