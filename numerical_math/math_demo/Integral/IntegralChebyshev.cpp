//IntegralChebyshev.cpp		 �б�ѩ�����
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
////#include "Integral.h"		//����ͷ�ļ�
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

using namespace std;		//���ֿռ�

int main(void)
{	
	double eps = FLOATERROR, a(2.5), b(8.4);
    
	cout << "IntegralChebyshev()" << endl << endl;

	double dValue = IntegralChebyshev(a, b, eps);

	cout << "dValue = " << dValue << endl << endl;
}

// ���㱻������ֵ
template <class _Ty>
_Ty FunctionValueCb(_Ty x)
{
	_Ty dValue;
	
	dValue = x * x + sin(x);

    return(dValue);
}
