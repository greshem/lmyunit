//PolyValueOneDim.cpp		һάʵ(��)����ʽ��ֵʾ��
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

using namespace std;
int main(void)
{
	cout.setf(ios::fixed|ios::left);
	cout.precision(6);
	//2*x^4 x=2 ��ֵ Ϊ    32. 
	double coff[]={0,0,0,0 ,2};
	valarray<double> vcoff(coff, sizeof(coff));
	
	double ret=PolyValueOneDim(vcoff, sizeof(coff)/sizeof(coff[0]) , 2);
	cout<< ret<<endl;
	

	//2*x^4 x=3 ��ֵ Ϊ    162 
	ret=PolyValueOneDim(vcoff, sizeof(coff)/sizeof(coff[0]) , 3);
	cout<< ret<<endl;
}
