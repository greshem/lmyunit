//---------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMStringH__
#define __LmyUnitMStringH__
//---------------------------------------------------------------------------------------------------------------------------------
//公共头文件
//.................................................................................................................................
#ifdef WINDOWSCODE
//.................................................................................................................................
//Windows操作系统
#include <windows.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <fstream>
#include <string> 
#include <sstream>
#include <iostream>
//.................................................................................................................................
#else
//.................................................................................................................................
//Linux操作系统
#include <assert.h>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <fstream>
#include <string> 
#include <sstream>
#include <iostream>


//.................................................................................................................................
#define		_snprintf			snprintf
#define		_vsnprintf			vsnprintf
#define		strnicmp			strncasecmp
#define		DWORD				unsigned long
#define		SOCKET				long
#define		closesocket			close
#define		SOCKET_ERROR		(-1)
#define		INVALID_SOCKET		(-1)
#define		__stdcall		
#define		WSAGetLastError()	(errno)		
#define		GetLastError()		(errno)
#define		BYTE				unsigned char
#define		WORD				unsigned short
#define		DWORD				unsigned long
#define		BOOL				bool
#define		FALSE				false
#define     TRUE				true
#define		__declspec(dllexport)
#define		__int64				unsigned long long
//........................................................................
template <class T1, class T2>
T1 max( T1 a, T2 b) { return a>b ? a : (T1)b;}

template <class T1, class T2>
T1 min( T1 a, T2 b) { return a<b ? a : (T1)b;}
//.................................................................................................................................
#endif
//---------------------------------------------------------------------------------------------------------------------------------
#define MSTRING_DEFAULT_BUFSIZE					256		//缺省字符串对象分配的空间
//.................................................................................................................................
#define ERROR_MSTRING_NOSUBSTRING		(ERROR_USER(0))	//没有匹配的子串
#define ERROR_MSTRING_INVALIDOFFSET		(ERROR_USER(1))	//无效的字符偏移量
//.................................................................................................................................
class MString
{
protected:
	char					*	m_StringPtr;
	char						m_DefaultBuf[MSTRING_DEFAULT_BUFSIZE];
	unsigned int				m_StringBufSize;
public:
	MString(void);
	MString(const char In);
	MString(const unsigned char In);
	MString(const char In,const unsigned short Count);
	MString(const unsigned char In,const unsigned short Count);
	MString(const short In);
	MString(const unsigned short In);
	MString(const int In);
	MString(const unsigned int In);
	MString(const long In);
	MString(const unsigned long In);
	MString(const char * In);
	MString(const MString & In);
	MString(const char *in, int length);

	friend std::ostream & operator << ( std::ostream &in , const MString  &in2);


	virtual ~MString();
public:
	MString & operator =  (const MString & In);
	MString & operator =  (const char * In);
	MString & operator += (const MString & In);
	MString & operator += (const char * In);
    MString   operator +  (const MString & In);
    MString   operator +  (const char * In);
public:
	friend MString operator + (const char * In1,const MString & In2);
	friend bool	   operator == (const MString & In1,const MString & In2);
	friend bool	   operator == (const MString & In1,const char * In2);
	friend bool	   operator == (const char * In1,const MString & In2);
	friend bool	   operator != (const MString & In1,const MString & In2);
	friend bool	   operator != (const MString & In1,const char * In2);
	friend bool	   operator != (const char * In1,const MString & In2);
	friend bool	   operator >  (const MString & In1,const MString & In2);
	friend bool	   operator >  (const MString & In1,const char * In2);
	friend bool	   operator >  (const char * In1,const MString & In2);
	friend bool	   operator >= (const MString & In1,const MString & In2);
	friend bool	   operator >= (const MString & In1,const char * In2);
	friend bool	   operator >= (const char * In1,const MString & In2);
	friend bool	   operator <  (const MString & In1,const MString & In2);
	friend bool	   operator <  (const MString & In1,const char * In2);
	friend bool	   operator <  (const char * In1,const MString & In2);
	friend bool	   operator <= (const MString & In1,const MString & In2);
	friend bool	   operator <= (const MString & In1,const char * In2);
	friend bool	   operator <= (const char * In1,const MString & In2);
public:
	char * c_str(void);
	unsigned int Length(void);
	void Upper(void);
	void Lower(void);
	int  StringPosition(const MString & In);
	int  StringPosition(const char * In);
	char & operator [] (const unsigned short In);
	int  SetAt(const unsigned short In,char CharValue);
	void FormatString(const char * Format,...);
	void Trim();
	void TrimLeft(void);
	void TrimRight(void);
public:
	static void Trim(char * String);
	static void TrimLeft(char * String);
	static void TrimRight(char * String);
	MString basename();
	MString dirname();


};
//---------------------------------------------------------------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------------------------------------------------------------
