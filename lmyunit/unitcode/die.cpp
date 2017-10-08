#include "die.h"

void die (char *format,...)
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
 void warn(char *format,...)
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
