//PolyValueOneDimGroup.cpp	求一维多项式组值示例
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
//#include <polynomials.h>	//多项式及连分式头文件
using namespace std;		//名字空间

//求多项式p(x,y)在多点处的函数值
int main(void)
{	
	cout << "PolyValueOneDimGroup()" << endl << endl;

	cout << "\t Group 1 " << endl;	//第一组求值
    
    double da[7] = {-20.0, 7.0, -7.0, 1.0, 3.0, -5.0, 2.0};
    double dx[6] = {0.9, -0.9, 1.1, -1.1, 1.3, -1.3};

	valarray<double> vda(da,7);
	valarray<double> vdx(dx,6);
	valarray<double> vdp(6);

	cout.setf(ios::fixed|ios::left);	//输出数据为定点法，靠左对齐
	cout.precision(6);					//精度6位

    PolyValueOneDimGroup(vda, vdx, vdp);

	cout << endl;
	size_t st;
    for(size_t st=0; st<6; st++)
	{
		cout << "x(" << st << ") = " << vdx[st];
		cout << "\t p(" << st << ") = "	<< vdp[st] << endl;
	}
    
	cout << endl << "\t Group 2 " << endl;	//第二组求值
	double db[16] = 
	{
		1.0,  2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,
		9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0
	};
	

	valarray<double> vdb(db,16);

	PolyValueOneDimGroup(vdb, vdx, vdp);

	cout << endl;

    for(st=0; st<6; st++)
	{
		cout << "x(" << st << ") = " << vdx[st];
		cout << "\t p(" << st << ") = "	<< vdp[st] << endl;
	}

	cout << endl;
}

