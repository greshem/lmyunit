//IntegralRomberg.cpp	 ���������
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

#include <iostream>		//���������ͷ�ļ�
////#include "Integral.h"	//����ͷ�ļ�
//########################################################################
//#include <QzjUnit.hpp>
//#include <MLmyUnit.hpp>
// #include <Baselib.hpp>
// #include <gtest/gtest.h>
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
using namespace std;	//���ֿռ�

int main(void)
{	
	double eps = FLOATERROR, a(0), b(1);

	cout << "IntegralRomberg()" << endl << endl;

	double dIntegralValue = IntegralRomberg(a,b,eps);

	cout << "IntegralValue = " << dIntegralValue << endl << endl;
}

// ���㱻������ֵ
template <class _Ty>
_Ty FunctionValueR(_Ty x)
{
	_Ty y;

	y = x / (4.0 + x * x);

    return(y);
}
