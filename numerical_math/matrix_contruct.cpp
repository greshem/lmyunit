
//########################################################################
//#include <QzjUnit.hpp>
//#include <MLmyUnit.hpp>
//#include <Baselib.hpp>
#include <gtest/gtest.h>
#include <fstream>
#include <string> 
#include <iostream>
#include <map>
#include <iostream> 
#include <algorithm>
#include <vector> 
#include <iterator>  
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <numerical_math.hpp>
int main()
{
	double a[4][4]={{1	,2	,3	,4	}, 
					{2.1,34	,5	, 67},
					{0.99,12,45	, 45},
					{3	,33	, 45, 100}};


double b[10][10]={
{9,1,9,1,3,7,9,4,3,5,}, 
{8,4,0,7,7,8,8,1,1,1,}, 
{3,6,4,3,1,9,6,8,4,9,}, 
{1,3,6,2,6,1,1,7,2,6,}, 
{9,8,1,5,4,0,3,7,2,0,}, 
{9,9,0,6,1,6,5,7,7,2,}, 
{3,9,0,7,7,7,7,6,6,6,}, 
{3,5,4,9,3,8,1,3,5,4,}, 
{1,2,1,1,1,2,3,0,3,2,}, 
{7,5,1,1,4,1,8,6,0,4,}, 
}; 


double c[10][10]={
{5,7,3,3,0,3,0,3,5,0,}, 
{8,8,5,5,4,1,0,4,6,9,}, 
{5,5,5,1,3,7,7,9,1,5,}, 
{6,5,8,3,0,3,7,7,9,8,}, 
{1,0,4,7,4,9,8,3,2,5,}, 
{5,9,4,5,3,7,7,2,4,3,}, 
{3,4,0,1,8,4,1,3,6,9,}, 
{8,4,2,4,0,0,0,4,7,9,}, 
{7,3,1,3,6,1,4,1,3,7,}, 
{5,8,0,8,9,4,7,1,2,4,}, 
}; 

double f[10][1]=
{{1},
 {2},
 {2},
 {2},
 {2},
 {2},
 {2},
 {2},
 {2},
 {2}};

	matrix<double>  matA(&a[0][0], 4, 4);
	matrix<double>  matB(&a[0][0], 4, 4);
	
	matrix<double> matC=matA*matB;
	//MatrixLinePrint(matA);			

	//MatrixLinePrint(matC);			
	matrix<double>  matD(&b[0][0], 10, 10);
	matrix<double>  matE(&c[0][0], 10, 10);
	matrix<double> matF(&f[0][0], 10, 1);
//	MatrixLinePrint(matD*matE);			
//	MatrixLinePrint(matD*matE);			
	MatrixLinePrint(matD*matF);			

}
