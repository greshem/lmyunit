//########################################################################
//#include <QzjUnit.hpp>
//#include <MLmyUnit.hpp>
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
#include "Random.hpp"
using namespace std;
int main(int argc, char *argv[])
{
	double seed=time(NULL);
	cout<<rand_01_One(seed);
	return 0;
}
