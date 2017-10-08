#ifndef __DUMPER__HEADER__
#define __DUMPER__HEADER__

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

#include "struct_define.hpp"
template <class T>void  dump( T &in)
{
	cout<<"not register type dump "<<endl;
	cout<< in <<endl;
	return ;
}
	


#endif //__DUMPER__HEADER__

