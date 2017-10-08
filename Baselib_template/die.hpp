
#ifndef __QzjUnit_DIE__
#define  __QzjUnit_DIE__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string> 
//#include <dirent.h>
#include <fstream>
#include <iterator>  
#include <vector> 
#include <algorithm>
#include <iostream> 
#include <map>
#include <stdarg.h>

template <typename > void die (char *format,...)
{
	static char tmp[1024];
	memset(tmp,'\0', sizeof(tmp));
	va_list(marker);
	va_start(marker, format);
	vsprintf(tmp, format, marker);
	va_end(marker);
	printf("%s\n", tmp);
	exit(0);

}

/*template<> void  die<char> (char *format,...)
{
	static char tmp[1024];
	memset(tmp,'\0', sizeof(tmp));
	va_list(marker);
	va_start(marker, format);
	vsprintf(tmp, format, marker);
	va_end(marker);
	printf("%s\n", tmp);
	exit(-1);
}*/
template <typename > void warn(char *format,...)
{
	static char tmp[1024];
	memset(tmp,'\0', sizeof(tmp));
	va_list(marker);
	va_start(marker, format);
	vsprintf(tmp, format, marker);
	va_end(marker);
	printf("%s\n", tmp);

}

/*template<> void warn<char> (char *format,...)
{
	static char tmp[1024];
	memset(tmp,'\0', sizeof(tmp));
	va_list(marker);
	va_start(marker, format);
	vsprintf(tmp, format, marker);
	va_end(marker);
	printf("%s\n", tmp);
}*/
#endif   
