//FourierSeriesApproach.cpp	����Ҷ�����ƽ�
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

#include <iostream>			//ģ���������������׼ͷ�ļ�
//#include <Transform.h>		//��ѧ�任ͷ�ļ�
using namespace std;		//���ֿռ�

int main(void)
{	
	valarray<long double> a(51);
	valarray<long double> b(51);
	valarray<long double> f(101);
	int i=0;
	
	long double h = 6.283185306 / 101.0;

	for(int i=0; i<101; i++)
    {
		long double ld = (i + 0.5) * h;
		f[i] = ld * ld;
	}
	
  	cout.setf(ios::fixed);	//�������Ϊ���㷨
	cout.precision(8);		//����8λ

    FourierSeriesApproach(f, a, b);

	cout << endl;

	for (i=0; i<51; i++)
		cout << "a(" << i << ") = " << a[i]
						<< "\t b(" << i << ") = " << b[i] << endl;
}


