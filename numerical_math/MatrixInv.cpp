
//#2010_09_24_23:02:46 add by greshem
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


int main()
{
	

double a[10][10]={
{8,2,5,9,2,1,3,8,3,4,}, 
{2,7,0,9,2,2,3,1,7,4,}, 
{8,3,5,9,8,9,0,5,0,9,}, 
{1,5,5,6,3,2,4,2,7,3,}, 
{4,2,5,0,1,7,9,9,2,7,}, 
{7,0,3,2,7,4,1,0,8,3,}, 
{9,7,9,0,9,3,1,9,4,9,}, 
{1,2,7,2,5,6,7,6,9,2,}, 
{2,0,8,9,6,4,7,2,6,2,}, 
{8,7,8,0,3,8,0,2,5,5,}, 
}; 
	matrix<double> matA(&a[0][0], 10, 10);
	matrix<double> matB(matA);
	cout<<"randk"<< MatrixRank(matA)<<endl ;
	if( MatrixInversionGS( matA ) > 0)
	{
		MatrixLinePrint(matA);
		matA=matA*matB;
		MatrixLinePrint(matA);
	}
	else
	{
		cout<<"ÇóÄæÊ§°Ü"<<endl;
	}
}
