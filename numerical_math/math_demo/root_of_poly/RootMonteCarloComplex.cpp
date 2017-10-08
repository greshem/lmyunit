//RootMonteCarloComplex.cpp		
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
//MonteCarlo���������Է���һ����

#define FM	//ע����У�������FunctionModule2()

#ifdef FM
	#define FunctionModule FunctionModule1
#else 
	#define FunctionModule FunctionModule2
#endif

#include <iostream>				//���������ͷ�ļ�
//#include "polynomials.h"		//����ʽ������ʽ��ֵͷ�ļ�
//#include "NonLinearEquation.h"	//�����Է���(��)���ͷ�ļ�
using namespace std;			//���ֿռ�

int main(void)
{
	int m = 10;
    double eps = FLOATERROR, b = 1;
	complex<double> cxy(0.5, 0.5);	//�Ա���
	        
	cout << "RootMonteCarloComplex()" << endl << endl;
    
    RootMonteCarloComplex(cxy,b,m,eps);

    cout << "z = " << cxy << endl;
}

//*	���㺯��ģ
template <class _Tz>
double FunctionModule1(_Tz cxy)	//f(x)���Ա���Ϊ����
{
	_Tz cmodule(cxy);
	double dCoff[3] = {13, -6, 1};
	valarray<double> vdCoff(dCoff,3);
	
	cmodule = PolyValueOneDim(vdCoff, 3, cxy);


	return(Abs(cmodule));
}

//*	���㺯��ģ
template <class _Tz>
double FunctionModule2(_Tz cxy)	//f(x)���Ա�����ϵ����Ϊ����
{
	_Tz cmodule(cxy);

	complex<double> cdCoff[3] = 
	{
		complex<double>(-1,2),
		complex<double>( 1,1), 
		complex<double>( 1,0)
	};

	valarray<complex<double> > vcdCoff(cdCoff,3);

	cmodule = PolyValueOneDim(vcdCoff, 3, cxy);

	return(Abs(cmodule));
}
