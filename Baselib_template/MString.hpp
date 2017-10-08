//#####################################################################################
#ifndef __LmyUnitMStringH__
#define __LmyUnitMStringH__
//qzj 20100628, 把 sprintf  long 的警告去掉。 
//#2010_08_06_16:38:33 add by qzjj
//把MString类整个都模板化了， 容易把所有的代码都写成头文件。 
//#####################################################################################
//公共头文件
//#####################################################################################
#ifdef WINDOWSCODE
//#####################################################################################
//Windows操作系统
#include <windows.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>

//#####################################################################################
#else
//#####################################################################################
//Linux操作系统
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <string>
#include <iostream>
//#####################################################################################
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
//#####################################################################################
template <class T1, class T2>
T1 max( T1 a, T2 b) { return a>b ? a : (T1)b;}

template <class T1, class T2>
T1 min( T1 a, T2 b) { return a<b ? a : (T1)b;}
//#####################################################################################
#endif
//#####################################################################################
#define MSTRING_DEFAULT_BUFSIZE					256		//缺省字符串对象分配的空间
//#####################################################################################
#define ERROR_MSTRING_NOSUBSTRING		(ERROR_USER(0))	//没有匹配的子串
#define ERROR_MSTRING_INVALIDOFFSET		(ERROR_USER(1))	//无效的字符偏移量
//#####################################################################################
using namespace std;
template <class T> class MString;

//template  < typename T>	MString<T> 		operator +  (const char * In1,const MString<T>  & In2);
template  <typename T > MString<T> operator +  (const char * In1,const MString<T> & In2)
{
	MString<T>							tempstring(In1);
	return(tempstring + In2);
}

template <typename T>  bool	   operator == (const MString<T>  & In1,const MString<T>  & In2);
template <typename T>  bool	   operator == (const MString<T>  & In1,const char * In2);
template <typename T>  bool	   operator == (const char * In1,const MString<T>  & In2);
template <typename T>  bool	   operator != (const MString <T> & In1,const MString<T>  & In2);
template <typename T>  bool	   operator != (const MString <T> & In1,const char * In2);
template <typename T>  bool	   operator != (const char * In1,const MString<T>  & In2);
template <typename T>  bool	   operator >  (const MString<T>  & In1,const MString<T>  & In2);
template <typename T>  bool	   operator >  (const MString<T>  & In1,const char * In2);
template <typename T>  bool	   operator >  (const char * In1,const MString<T>  & In2);
template <typename T>  bool	   operator >= (const MString<T>  & In1,const MString<T>  & In2);
template <typename T>  bool	   operator >= (const MString<T>  & In1,const char * In2);
template <typename T>  bool	   operator >= (const char * In1,const MString<T>  & In2);
template <typename T>  bool	   operator <  (const MString<T>  & In1,const MString<T>  & In2);
template <typename T>  bool	   operator <  (const MString<T>  & In1,const char * In2);
template <typename T>  bool	   operator <  (const char * In1,const MString<T>  & In2);
template <typename T>  bool	   operator <= (const MString<T>  & In1,const MString<T>  & In2);
template <typename T>  bool	   operator <= (const MString<T>  & In1,const char * In2);
template <typename T>  bool	   operator <= (const char * In1,const MString<T>  & In2);
template <typename T>  ostream & operator << ( ostream &in , const MString<T>  &in2);
template <typename T>  MString<T> add   (const char * In1,const MString<T> & In2)
{
	MString<T>							tempstring(In1);
	return(tempstring + In2);

}


template <typename  T=char> class MString

{
	//friend class   ostream;
//protected:
public:
	char							*	m_StringPtr;
	char							m_DefaultBuf[MSTRING_DEFAULT_BUFSIZE];
	unsigned int				m_StringBufSize;
public:
	MString<T>(void);
	MString(const char In);
	MString(const unsigned char In);
	MString(const char In,const unsigned short Count);
	MString(const unsigned char In,const unsigned short Count);
	MString(const short In);
	MString(const unsigned short In);
	MString(const int In);
	MString(const unsigned int In);
	MString(const long In);
	MString(const char  *in, int length);
	MString(const unsigned long In);
	MString<T>(const char * In);
	MString<T>(const MString<T> & In);
	virtual ~MString();
public:
	MString<T> & operator =  (const MString<T> & In);
	MString<T> & operator =  (const char * In);
	MString<T> & operator += (const MString<T> & In);
	MString<T> & operator += (const char * In);
	MString<T>   operator +  (const MString<T> & In);
	MString<T>   operator +  (const char * In);
	MString<T>   dirname();
	MString<T>   basename();
public:
	//friend  bool 	   IsBigger<T>( const T * In1,const MString<T>  & In2)  ;
	//friend 	MString<T> operator + <> (const char * In1,const MString<T>  & In2);
	friend  bool	   operator == <T>(const MString<T> & In1,const MString<T> & In2);
	friend 	MString<T> add <T> (const char * In1,const MString<T>  & In2);
	friend  bool	   operator == <T>(const MString<T> & In1,const char * In2);
	friend  bool	   operator == <T>(const char * In1,const MString<T> & In2);
	friend  bool	   operator != <T>(const MString <T>& In1,const MString<T> & In2);
	friend  bool	   operator != <T>(const MString <T>& In1,const char * In2);
	friend  bool	   operator != <T>(const char * In1,const MString<T> & In2);
public:
	//friend  bool 	   IsBigger<T>( const T * In1,const MString<T>  & In2)  ;
	//friend 	MString<T> operator + <> (const char * In1,const MString<T>  & In2);
	friend  bool	   operator == <T>(const MString<T> & In1,const MString<T> & In2);
	friend 	MString<T> add <T> (const char * In1,const MString<T>  & In2);
	friend  bool	   operator == <T>(const MString<T> & In1,const char * In2);
	friend  bool	   operator == <T>(const char * In1,const MString<T> & In2);
	friend  bool	   operator != <T>(const MString <T>& In1,const MString<T> & In2);
	friend  bool	   operator != <T>(const MString <T>& In1,const char * In2);
	friend  bool	   operator != <T>(const char * In1,const MString<T> & In2);
	friend  bool	   operator >  <T>(const MString<T> & In1,const MString<T> & In2);
	friend  bool	   operator >  <T>(const MString<T> & In1,const char * In2);
	friend  bool	   operator >  <T>(const char * In1,const MString<T> & In2);
	friend  bool	   operator >= <T>(const MString<T> & In1,const MString<T> & In2);
	friend  bool	   operator >= <T>(const MString<T> & In1,const char * In2);
	friend  bool	   operator >= <T>(const char * In1,const MString<T> & In2);
	friend  bool	   operator <  <T>(const MString<T> & In1,const MString<T> & In2);
	friend  bool	   operator <  <T>(const MString<T> & In1,const char * In2);
	friend  bool	   operator <  <T>(const char * In1,const MString<T> & In2);
	friend  bool	   operator <= <T>(const MString<T> & In1,const MString<T> & In2);
	friend  bool	   operator <= <T>(const MString<T> & In1,const char * In2);
	friend  bool	   operator <= <T>(const char * In1,const MString<T> & In2);
	friend  ostream & operator << <T>( ostream &in , const MString<T> &in2);

public:
		char * c_str(void);
		unsigned int Length(void);
		void Upper(void);
		void Lower(void);
		int  StringPosition(const MString<T> & In);
		int  StringPosition(const char * In);
		char & operator [] (const unsigned short In);
		int  SetAt(const unsigned short In,char CharValue);
		void FormatString(const char * Format,...);
		void TrimLeft(void);
		void TrimRight(void);
		void Trim(void);
public:
		static void TrimLeft(char * String);
		static void TrimRight(char * String);
		static void Trim(char *String);
};
//#####################################################################################
//#####################################################################################
//#####################################################################################
//#include "MString.h"
//#include "MObject.h"
//#####################################################################################
 template  <typename T > MString<T>::MString(void)
{
	m_StringPtr = m_DefaultBuf;
	m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
	memset(m_StringPtr,0,m_StringBufSize);
}
//#####################################################################################
 template  <typename T > MString<T>::MString(const char In)
{
	m_StringPtr = m_DefaultBuf;
	m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
	_snprintf(m_StringPtr,m_StringBufSize,"%c",In);
}
//#####################################################################################
 template  <typename T > MString<T>::MString(const unsigned char In)
{
	m_StringPtr = m_DefaultBuf;
	m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
	_snprintf(m_StringPtr,m_StringBufSize,"%c",In);
}

//########################################################################
//用 in 的str 来填充本字符串 是本字符串 达到 length长度。 
template <typename T> MString<T>::MString(const char *in, int length)
{
		
	register unsigned int					errorcode;
	//用 in 的字符填充 本字符串 达到 length长度。 
	assert(in!=NULL);
	
	int partlen=strlen(in);
	int i=0;	
	int cur_offset=0;;
	if ( (length + 1) >= MSTRING_DEFAULT_BUFSIZE )
	{
		errorcode = (((length + 1) >> 8) + 1) << 8;
		m_StringPtr = new char[errorcode];
		assert(m_StringPtr != NULL);
		if ( m_StringPtr != NULL )
		{
			memset(m_StringPtr,'\0',length);
			//-------------------------------
			//memset 的变体
			cur_offset=0;
			for( i=0; i<int(length/partlen);i++)
			{
				memcpy(m_StringPtr+i*partlen,in, partlen);
				cur_offset+=partlen;
			}
			for(i=0; i<length%partlen; i++)
			{
				m_StringPtr[cur_offset+i]=in[i];	
			}
			//-------------------------------
				
			m_StringPtr[length] = 0;
			m_StringBufSize = errorcode;
		}
		else
		{
			m_StringPtr = m_DefaultBuf;
			m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
			memset(m_StringPtr,'\0',m_StringBufSize - 1);
			//-------------------------------
			//memset 的变体
			cur_offset=0;
			for( i=0; i<int(length/partlen);i++)
			{
				memcpy(m_StringPtr+i*partlen,in, partlen);
				cur_offset+=partlen;
			}
			for(i=0; i<length%partlen; i++)
			{
				m_StringPtr[cur_offset+i]=in[i];	
			}
			//-------------------------------


			m_StringPtr[m_StringBufSize-1] = 0;	
		}
	}
	else
	{
		m_StringPtr = m_DefaultBuf;
		m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
		memset(m_StringPtr,'\0',length);
		//-------------------------------
		//memset 的变体
		cur_offset=0;
		for( i=0; i<int(length/partlen);i++)
		{
			memcpy(m_StringPtr+i*partlen,in, partlen);
			cur_offset+=partlen;
		}
		for(i=0; i<length%partlen; i++)
		{
			m_StringPtr[cur_offset+i]=in[i];	
		}
		//-------------------------------

		m_StringPtr[length] = 0;
	}

}

//#####################################################################################
 template  <typename T > MString<T>::MString(const char In,const unsigned short Count)
{
	register unsigned int					errorcode;

	if ( (Count + 1) >= MSTRING_DEFAULT_BUFSIZE )
	{
		errorcode = (((Count + 1) >> 8) + 1) << 8;
		m_StringPtr = new char[errorcode];
		assert(m_StringPtr != NULL);
		if ( m_StringPtr != NULL )
		{
			memset(m_StringPtr,In,Count);
			m_StringPtr[Count] = 0;
			m_StringBufSize = errorcode;
		}
		else
		{
			m_StringPtr = m_DefaultBuf;
			m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
			memset(m_StringPtr,In,m_StringBufSize - 1);
			m_StringPtr[m_StringBufSize-1] = 0;	
		}
	}
	else
	{
		m_StringPtr = m_DefaultBuf;
		m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
		memset(m_StringPtr,In,Count);
		m_StringPtr[Count] = 0;
	}
}
//#####################################################################################
 template  <typename T > MString<T>::MString(const unsigned char In,const unsigned short Count)
{
	register unsigned int					errorcode;

	if ( (Count + 1) >= MSTRING_DEFAULT_BUFSIZE )
	{
		errorcode = (((Count + 1) >> 8) + 1) << 8;
		m_StringPtr = new char[errorcode];
		assert(m_StringPtr != NULL);
		if ( m_StringPtr != NULL )
		{
			memset(m_StringPtr,In,Count);
			m_StringPtr[Count] = 0;
			m_StringBufSize = errorcode;
		}
		else
		{
			m_StringPtr = m_DefaultBuf;
			m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
			memset(m_StringPtr,In,m_StringBufSize - 1);
			m_StringPtr[m_StringBufSize-1] = 0;	
		}
	}
	else
	{
		m_StringPtr = m_DefaultBuf;
		m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
		memset(m_StringPtr,In,Count);
		m_StringPtr[Count] = 0;
	}
}
//#####################################################################################
 template  <typename T > MString<T>::MString(const short In)
{
	m_StringPtr = m_DefaultBuf;
	m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
	_snprintf(m_StringPtr,m_StringBufSize,"%d",In);
}
//#####################################################################################
 template  <typename T > MString<T>::MString(const unsigned short In)
{
	m_StringPtr = m_DefaultBuf;
	m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
	_snprintf(m_StringPtr,m_StringBufSize,"%d",In);
}
//#####################################################################################
 template  <typename T > MString<T>::MString(const int In)
{
	m_StringPtr = m_DefaultBuf;
	m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
	_snprintf(m_StringPtr,m_StringBufSize,"%d",In);
}
//#####################################################################################
 template  <typename T > MString<T>::MString(const unsigned int In)
{
	m_StringPtr = m_DefaultBuf;
	m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
	_snprintf(m_StringPtr,m_StringBufSize,"%d",In);
}
//#####################################################################################
/*MString::MString(const int In)
{
	m_StringPtr = m_DefaultBuf;
	m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
	_snprintf(m_StringPtr,m_StringBufSize,"%d",In);
}*/
//#####################################################################################
/*MString::MString(const unsigned int In)
{
	m_StringPtr = m_DefaultBuf;
	m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
	_snprintf(m_StringPtr,m_StringBufSize,"%d",In);
}*/
//#####################################################################################
 template  <typename T > MString<T>::MString(const char * In)
{
	register unsigned int					errorcode;

	errorcode = strlen(In) + 1;
	if ( errorcode >= MSTRING_DEFAULT_BUFSIZE )
	{
		errorcode = ((errorcode >> 8) + 1) << 8;
		m_StringPtr = new char[errorcode];
		assert(m_StringPtr != NULL);
		if ( m_StringPtr != NULL )
		{
			strncpy(m_StringPtr,In,errorcode);
			m_StringBufSize = errorcode;
		}
		else
		{
			m_StringPtr = m_DefaultBuf;
			m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
			strncpy(m_StringPtr,In,m_StringBufSize);
			m_StringPtr[m_StringBufSize-1] = 0;
		}
	}
	else
	{
		m_StringPtr = m_DefaultBuf;
		m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
		strncpy(m_StringPtr,In,m_StringBufSize);
	}
}
//#####################################################################################
 template  <typename T > MString<T>::MString(const MString<T> & In)
{
	register unsigned int					errorcode;

	errorcode = strlen(In.m_StringPtr) + 1;
	if ( errorcode >= MSTRING_DEFAULT_BUFSIZE )
	{
		errorcode = ((errorcode >> 8) + 1) << 8;
		m_StringPtr = new char[errorcode];
		assert(m_StringPtr != NULL);
		if ( m_StringPtr != NULL )
		{
			strncpy(m_StringPtr,In.m_StringPtr,errorcode);
			m_StringBufSize = errorcode;
		}
		else
		{
			m_StringPtr = m_DefaultBuf;
			m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
			strncpy(m_StringPtr,In.m_StringPtr,m_StringBufSize);	
			m_StringPtr[m_StringBufSize-1] = 0;
		}
	}
	else
	{
		m_StringPtr = m_DefaultBuf;
		m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
		strncpy(m_StringPtr,In.m_StringPtr,m_StringBufSize);
	}
}
//#####################################################################################
template< typename T> MString<T>::~MString()
{
	if ( m_StringPtr != m_DefaultBuf )
	{
		delete [] m_StringPtr;
		m_StringPtr = m_DefaultBuf;
	}
	m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
}
//#####################################################################################
 template  <typename T > MString<T> & MString<T>::operator =  (const MString<T>& In)
{
	register unsigned int					errorcode;

	errorcode = strlen(In.m_StringPtr) + 1;
	if ( errorcode >= m_StringBufSize )
	{
		if ( m_StringPtr != m_DefaultBuf )
		{
			delete [] m_StringPtr;
		}

		errorcode = ((errorcode >> 8) + 1) << 8;
		m_StringPtr = new char[errorcode];
		assert(m_StringPtr != NULL );
		if ( m_StringPtr != NULL )
		{
			m_StringBufSize = errorcode;
			strncpy(m_StringPtr,In.m_StringPtr,m_StringBufSize);
		}
		else
		{
			m_StringPtr = m_DefaultBuf;
			strncpy(m_StringPtr,In.m_StringPtr,m_StringBufSize);
			m_StringPtr[m_StringBufSize-1] = 0;
		}
	}
	else
	{
		strncpy(m_StringPtr,In.m_StringPtr,m_StringBufSize - strlen(m_StringPtr) );
	}

	return( * this);
}
//#####################################################################################
 template  <typename T > MString <T>& MString<T>::operator =  (const char * In)
{
	register unsigned int					errorcode;

	errorcode = strlen(In) + 1;
	if ( errorcode >= m_StringBufSize )
	{
		if ( m_StringPtr != m_DefaultBuf )
		{
			delete [] m_StringPtr;
		}

		errorcode = ((errorcode >> 8) + 1) << 8;
		m_StringPtr = new char[errorcode];
		assert(m_StringPtr != NULL );
		if ( m_StringPtr != NULL )
		{
			m_StringBufSize = errorcode;
			strncpy(m_StringPtr,In,m_StringBufSize);
		}
		else
		{
			m_StringPtr = m_DefaultBuf;
			strncpy(m_StringPtr,In,m_StringBufSize);	
			m_StringPtr[m_StringBufSize-1] = 0;
		}
	}
	else
	{
		strncpy(m_StringPtr,In,m_StringBufSize);
	}

	return( * this);
}
//#####################################################################################
template < typename T> MString<T> & MString<T>::operator += (const MString<T> & In)
{
	register unsigned int					errorcode;

	errorcode = strlen(m_StringPtr) + strlen(In.m_StringPtr) + 1;
	if ( errorcode >= m_StringBufSize )
	{
		if ( m_StringPtr != m_DefaultBuf )
		{
			delete [] m_StringPtr;
		}

		errorcode = ((errorcode >> 8) + 1) << 8;
		m_StringPtr = new char[errorcode];
		assert(m_StringPtr != NULL );
		if ( m_StringPtr != NULL )
		{
			m_StringBufSize = errorcode;
			strncat(m_StringPtr,In.m_StringPtr,m_StringBufSize);
		}
		else
		{
			m_StringPtr = m_DefaultBuf;
			strncat(m_StringPtr,In.m_StringPtr,m_StringBufSize - strlen( m_StringPtr )-1 );	
		}
	}
	else
	{
		strncat(m_StringPtr,In.m_StringPtr,m_StringBufSize);
	}

	return(* this);
}
//#####################################################################################
template  <typename T > MString<T> & MString<T>::operator += (const char * In)
{
	register unsigned int					errorcode;

	errorcode = strlen(m_StringPtr) + strlen(In) + 1;
	if ( errorcode >= m_StringBufSize )
	{
		if ( m_StringPtr != m_DefaultBuf )
		{
			delete [] m_StringPtr;
		}

		errorcode = ((errorcode >> 8) + 1) << 8;
		m_StringPtr = new char[errorcode];
		assert(m_StringPtr != NULL );
		if ( m_StringPtr != NULL )
		{
			m_StringBufSize = errorcode;
			strncat(m_StringPtr,In,m_StringBufSize);
		}
		else
		{
			m_StringPtr = m_DefaultBuf;
			strncat(m_StringPtr,In,m_StringBufSize - strlen(m_StringPtr)-1 );	
		}
	}
	else
	{
		strncat(m_StringPtr,In,m_StringBufSize);
	}

	return(* this);
}
//#####################################################################################
template  <typename T >  MString<T>   MString<T>::operator +  (const MString<T> & In)
{
	MString<T>						tempstring(m_StringPtr);

	tempstring += In;

	return(tempstring);
}
//#####################################################################################
 template  <typename T > MString<T>  MString<T>::operator +  (const char* In)
{
	MString<T>							tempstring(m_StringPtr);

	tempstring += In;

	return(tempstring);
}
//#####################################################################################
//#####################################################################################
 template  <typename T > bool   operator == (const MString<T> & In1,const MString<T> & In2)
{
	if ( strncmp(In1.m_StringPtr,In2.m_StringPtr,max(In1.m_StringBufSize,In2.m_StringBufSize)) == 0 )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
///###############################################################################/
 template  <typename T > bool   operator == (const MString <T>& In1,const char * In2)
{
	if ( strncmp(In1.m_StringPtr,In2,max(In1.m_StringBufSize,strlen(In2))) == 0 )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//#####################################################################################
 template  <typename T > bool   operator == (const char * In1,const MString<T> & In2)
{
	if ( strncmp(In1,In2.m_StringPtr,max(strlen(In1),In2.m_StringBufSize)) == 0 )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//#####################################################################################
 template  <typename T > bool   operator != (const MString<T> & In1,const MString <T>& In2)
{
	if ( strncmp(In1.m_StringPtr,In2.m_StringPtr,max(In1.m_StringBufSize,In2.m_StringBufSize)) != 0 )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//#####################################################################################
 template  <typename T > bool   operator != (const MString <T>& In1,const char * In2)
{
	if ( strncmp(In1.m_StringPtr,In2,max(In1.m_StringBufSize,strlen(In2))) != 0 )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//#####################################################################################
 template  <typename T > bool   operator != (const char * In1,const MString <T> & In2)
{
	if ( strncmp(In1,In2.m_StringPtr,max(strlen(In1),In2.m_StringBufSize)) != 0 )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//#####################################################################################
 template  <typename T > bool   operator >  (const MString<T> & In1,const MString <T>& In2)
{
	if ( strncmp(In1.m_StringPtr,In2.m_StringPtr,max(In1.m_StringBufSize,In2.m_StringBufSize)) > 0 )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//#####################################################################################
 template  <typename T > bool   operator >  (const MString<T> & In1,const char * In2)
{
	if ( strncmp(In1.m_StringPtr,In2,max(In1.m_StringBufSize,strlen(In2))) > 0 )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//#####################################################################################
 template  <typename T > bool   operator >   (const char * In1,const MString <T>& In2)
{
	if ( strncmp(In1,In2.m_StringPtr,max(strlen(In1),In2.m_StringBufSize)) > 0 )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//#####################################################################################
 template  <typename T > bool   operator >= (const MString <T> & In1,const MString <T>& In2)
{
	if ( strncmp(In1.m_StringPtr,In2.m_StringPtr,max(In1.m_StringBufSize,In2.m_StringBufSize)) >= 0 )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//#####################################################################################
 template  <typename T > bool   operator >= (const MString <T> & In1,const char * In2)
{
	if ( strncmp(In1.m_StringPtr,In2,max(In1.m_StringBufSize,strlen(In2))) >= 0 )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//#####################################################################################
 template  <typename T > bool   operator >= (const char * In1,const MString <T> & In2)
{
	if ( strncmp(In1,In2.m_StringPtr,max(strlen(In1),In2.m_StringBufSize)) >= 0 )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//#####################################################################################
 template  <typename T > bool   operator <  (const MString <T>& In1,const MString <T>& In2)
{
	if ( strncmp(In1.m_StringPtr,In2.m_StringPtr,max(In1.m_StringBufSize,In2.m_StringBufSize)) < 0 )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//#####################################################################################
 template  <typename T > bool   operator <  (const MString <T>& In1,const char * In2)
{
	if ( strncmp(In1.m_StringPtr,In2,max(In1.m_StringBufSize,strlen(In2))) < 0 )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//#####################################################################################
 template  <typename T > bool   operator <  (const char * In1,const MString <T>& In2)
{
	if ( strncmp(In1,In2.m_StringPtr,max(strlen(In1),In2.m_StringBufSize)) < 0 )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//#####################################################################################
 template  <typename T > bool   operator <= (const MString <T>& In1,const MString <T>& In2)
{
	if ( strncmp(In1.m_StringPtr,In2.m_StringPtr,max(In1.m_StringBufSize,In2.m_StringBufSize)) <= 0 )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//#####################################################################################
 template  <typename T > bool   operator <= (const MString <T>& In1,const char * In2)
{
	if ( strncmp(In1.m_StringPtr,In2,max(In1.m_StringBufSize,strlen(In2))) <= 0 )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//#####################################################################################
 template  <typename T > bool   operator <= (const char * In1,const MString <T>& In2)
{
	if ( strncmp(In1,In2.m_StringPtr,min(strlen(In1),In2.m_StringBufSize)) <= 0 )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}

 template  <typename T > ostream & operator << ( ostream &in , const MString <T>&in2)
{
	in<<in2.m_StringPtr;
	return in;
}

//#####################################################################################
 template  <typename T > unsigned int MString<T>::Length(void)
{
	return(strlen(m_StringPtr));
}
//#####################################################################################
 template  <typename T > void MString<T>::Upper(void)
{
	#ifdef WINDOWSCODE
		_strupr(m_StringPtr);
	#else
		register unsigned int			i;
		
		for ( i=0;i<=strlen(m_StringPtr)-1;i++ )
		{
			if ( m_StringPtr[i] >= 97 && m_StringPtr[i] <= 122 )
			{
				m_StringPtr[i] -= 32;	
			}
		}
	#endif
}
//#####################################################################################
 template  <typename T > void MString<T>::Lower(void)
{
	#ifdef WINDOWSCODE
		_strlwr(m_StringPtr);
	#else
		register unsigned int			i;
		
		for ( i=0;i<=strlen(m_StringPtr)-1;i++ )
		{
			if ( m_StringPtr[i] >= 65 && m_StringPtr[i] <= 90 )
			{
				m_StringPtr[i] += 32;	
			}
		}
	#endif
}
//#####################################################################################
 template  <typename T > int  MString<T>::StringPosition(const MString <T>& In)
{
	char					*	tempcharptr;

	if ( (tempcharptr = strstr(m_StringPtr,In.m_StringPtr)) == NULL )
	{
//		return(ERROR_MSTRING_NOSUBSTRING);
		return -1;
	}
	else
	{
		return(tempcharptr - m_StringPtr);
	}
}
//#####################################################################################
 template  <typename T > int  MString<T>::StringPosition(const char * In)
{
	char					*	tempcharptr;

	if ( (tempcharptr = strstr(m_StringPtr,In)) == NULL )
	{
//		return(ERROR_MSTRING_NOSUBSTRING);
		return -1;
	}
	else
	{
		return(tempcharptr - m_StringPtr);
	}
}
//#####################################################################################
//
 template  <typename T > char & MString<T>::operator [] (const unsigned short In)
{
	assert(In < m_StringBufSize);
	if ( In < m_StringBufSize )
	{
		return(m_StringPtr[In]);
	}
	else
	{
		return(m_StringPtr[0]);	
	}
}
//#####################################################################################
 template  <typename T > int  MString<T>::SetAt(const unsigned short In,char CharValue)
{
	assert(In < m_StringBufSize);
	if ( In < m_StringBufSize )
	{
		m_StringPtr[In] = CharValue;
		return(1);
	}
	else
	{
//		return(ERROR_MSTRING_INVALIDOFFSET);
		return -1;
	}
}
//#####################################################################################
 template  <typename T > void MString<T>::FormatString(const char * Format,...)
{
	va_list						marker;

	va_start(marker,Format);
	_vsnprintf(m_StringPtr,m_StringBufSize,Format,marker);
	va_end( marker );
}
//#####################################################################################
 template  <typename T > void MString<T>::TrimLeft(void)
{
	register int				errorcode;
	register int				offset = 0;
	register int				i;

	errorcode = strlen(m_StringPtr);
	for ( i=0;i<=errorcode-1;i++ )
	{
		if ( m_StringPtr[i] != ' ' && m_StringPtr[i] != 0x09  && m_StringPtr[i] != 0x0D && m_StringPtr[i] != 0x0A )
		{
			offset = i;
			break;
		}
	}

	if ( offset != 0 )
	{
		memmove(m_StringPtr,m_StringPtr + offset,errorcode - offset);
		m_StringPtr[errorcode - offset] = 0;
	}
}
//#####################################################################################
 template  <typename T > void MString<T>::TrimRight(void)
{
	register int				errorcode;
	register int				i;

	errorcode = strlen(m_StringPtr);
	for ( i=errorcode-1;i>=0;i-- )
	{
		if ( m_StringPtr[i] != ' ' && m_StringPtr[i] != 0x09  && m_StringPtr[i] != 0x0D && m_StringPtr[i] != 0x0A )
		{
			m_StringPtr[i+1] = 0;
			return;
		}
	}
	m_StringPtr[0] = 0;
}
template  <typename T> void MString <T> ::Trim()
{
		TrimRight();
		TrimLeft();
}
//#####################################################################################
template  <typename T > char * MString<T>::c_str(void)
{
	return(m_StringPtr);
}
//#####################################################################################
template <typename T > void MString<T>::TrimLeft(char * String)
{
	register int				errorcode;
	register int				offset = 0;
	register int				i;
	
	errorcode = strlen(String);
	for ( i=0;i<=errorcode-1;i++ )
	{
		if ( String[i] != ' ' && String[i] != 0x09 && String[i] != 0x0D && String[i] != 0x0A )
		{
			offset = i;
			break;
		}
	}
	
	if ( offset != 0 )
	{
		memmove(String,String + offset,errorcode - offset);
		String[errorcode - offset] = 0;
	}
}
//#####################################################################################
template < typename T> void MString<T>::TrimRight(char * String)
{
	register int				errorcode;
	register int				i;
	
	errorcode = strlen(String);
	for ( i=errorcode-1;i>=0;i-- )
	{
		if ( String[i] != ' ' && String[i] != 0x09 && String[i] != 0x0D && String[i] != 0x0A )
		{
			String[i+1] = 0;
			return;
		}
	}
	
	String[0] = 0;
}

template < typename T> void MString<T>::Trim(char * String)
{
		MString<T>::TrimRight(String);
		MString<T>::TrimLeft(String);
}
template < typename T> MString<T>   MString<T>::dirname()
{
	int len=strlen(m_StringPtr);
	char *tmpBuf=(char *)malloc(len);
	memset(tmpBuf, '\0', len);
	int i=0;
	for(i=len-1; i>=0; i--)
	{
		if(m_StringPtr[i]=='/')
		{
			break;
		}
	}
	strncpy(tmpBuf, m_StringPtr, i+1);	
	 MString<T> tmp(tmpBuf);
	free(tmpBuf);
	return tmp;
}

template< typename T> MString<T> MString<T>::basename()
{
		
	int len=strlen(m_StringPtr);
	char *tmpBuf=(char *)malloc(len);
	memset(tmpBuf, '\0', len);
	int i=0;
	for(i=len-1; i>=0; i--)
	{
		if(m_StringPtr[i]=='/')
		{
			break;
		}
	}
	strncpy(tmpBuf, m_StringPtr+i+1, len-i);	
	 MString<T> tmp(tmpBuf);
	free(tmpBuf);
	return tmp;
}


#endif
//#####################################################################################
/*int main()
{
      unsigned char word='a';
      MString<char >  a(word, 10);
      a+="qianzhogjie\n";
      a+="zhognjie\n";
      a+="afasfasfsa\n";
//	cout<<a<<endl;
		printf("%s\n", a.c_str());
   //   getchar();
	return 1;
}*/

