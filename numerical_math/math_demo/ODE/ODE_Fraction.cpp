//ODE_Fraction.cpp		����һ������ʽ��
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

#include <iostream>							//���������ͷ�ļ�
//#include "OrdinaryDifferentialEguation.h"	//��ⳣ΢�ַ���(��)ͷ�ļ�
using namespace std;						//���ֿռ�

int main(void)
{	
	double dy[2] = {1.0, 0.0}, t(0.0), h(0.1), eps(FLOATERROR);
	valarray<double> y(dy, 2);
	
  	cout.setf(ios::fixed);	//�������Ϊ���㷨
	cout.precision(6);		//����6λ

	cout << " t = " << t << "\t y[0] = " << dy[0] << "\t y[1] = " << dy[1] << endl;

	for(int i=0; i<10; i++)
	{
		ODE_Fraction(t, h, y, eps);
		t = t + h;
		cout << " t = " << t << "\t y[0] = " << y[0] << "\t y[1] = " << y[1] << endl;
	}
}

//����΢�ַ������и������Ҷ˺���ֵ
template <class _Ty>
void FunctionValueF(_Ty t, valarray<_Ty>& y, valarray<_Ty>& d)
{
	int n = y.size();	//΢�ַ������з��̵ĸ�����Ҳ��δ֪�����ĸ���

    d[0] = -y[1];
	d[1] = y[0]; 
}

