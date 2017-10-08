//LE_SparseEuationTotalChoiceGaussJordan.cpp  
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
//������ϡ�跽�����ȫѡ��Ԫ��˹-Լ����ȥ��

#include <iostream>				//���������ͷ�ļ�
//#include "LinearEquation.h"		//���Է���(��)���ͷ�ļ�

int main()
{
	int i;
    
	double a[8][8] = 
	{
		{0.0, 0.0, -1.0,   0.0,   0.0,   0.0,  2.0,  0.0},
		{0.0, 6.0,  0.0,   0.0,   0.0,  -6.0,  0.0,  0.0},
		{0.0, 0.0,  0.0,   2.0,   0.0,   0.0,  0.0, -4.0},
		{3.0, 0.0,  0.0,   0.0,  -2.0,   0.0,  1.0,  0.0},
		{0.0, 0.0,  6.0,   0.0,   0.0,   0.0,  5.0,  0.0},
		{1.0, 0.0,  0.0,   0.0,  -3.0,   0.0,  0.0,  2.0},
		{0.0, 4.0,  0.0,  -1.0,   0.0,   0.0,  0.0,  0.0},
		{0.0, 0.0,  1.0,   0.0,  -1.0,   0.0,  0.0, -2.0}
	};

	double b[8] = {4.0, 6.0, -8.0, -2.0, 27.0, -9.0, 2.0, -4.0};

	valarray<double> bb(b,8);
	matrix<double> aa(&a[0][0], 8, 8);
	    
	if (LE_SparseEuationTotalChoiceGaussJordan(aa, bb) != 0)
      for (i=0; i<8; i++)
	  {
		  cout << "x(" << i << ") = " << bb[i] << endl;
	  }
	  cout<<endl;       
}
