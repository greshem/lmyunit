//PolyValueOneDim.cpp		一维实(复)多项式求值示例
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

#include <iostream>			//输入输出流头文件

using namespace std;
int main(void)
{
	cout.setf(ios::fixed|ios::left);
	cout.precision(6);
	//2*x^4 x=2 的值 为    32. 
	double coff[]={0,0,0,0 ,2};
	valarray<double> vcoff(coff, sizeof(coff));
	
	double ret=PolyValueOneDim(vcoff, sizeof(coff)/sizeof(coff[0]) , 2);
	cout<< ret<<endl;
	

	//2*x^4 x=3 的值 为    162 
	ret=PolyValueOneDim(vcoff, sizeof(coff)/sizeof(coff[0]) , 3);
	cout<< ret<<endl;
}
