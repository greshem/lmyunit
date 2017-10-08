//---------------------------------------------------------------------------------------------------------------------------------
#include "mstring.h"
#include "mobject.h"
//---------------------------------------------------------------------------------------------------------------------------------
MString::MString(void)
{
	m_StringPtr = m_DefaultBuf;
	m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
	memset(m_StringPtr,0,m_StringBufSize);
}
//.................................................................................................................................
MString::MString(const char In)
{
	m_StringPtr = m_DefaultBuf;
	m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
	_snprintf(m_StringPtr,m_StringBufSize,"%c",In);
}
//.................................................................................................................................
MString::MString(const unsigned char In)
{
	m_StringPtr = m_DefaultBuf;
	m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
	_snprintf(m_StringPtr,m_StringBufSize,"%c",In);
}
//.................................................................................................................................
MString::MString(const char In,const unsigned short Count)
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
//.................................................................................................................................
MString::MString(const unsigned char In,const unsigned short Count)
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
//.................................................................................................................................
MString::MString(const short In)
{
	m_StringPtr = m_DefaultBuf;
	m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
	_snprintf(m_StringPtr,m_StringBufSize,"%d",In);
}
//.................................................................................................................................
MString::MString(const unsigned short In)
{
	m_StringPtr = m_DefaultBuf;
	m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
	_snprintf(m_StringPtr,m_StringBufSize,"%d",In);
}
//.................................................................................................................................
MString::MString(const int In)
{
	m_StringPtr = m_DefaultBuf;
	m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
	_snprintf(m_StringPtr,m_StringBufSize,"%d",In);
}
//.................................................................................................................................
MString::MString(const unsigned int In)
{
	m_StringPtr = m_DefaultBuf;
	m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
	_snprintf(m_StringPtr,m_StringBufSize,"%d",In);
}
//.................................................................................................................................
MString::MString(const long In)
{
	m_StringPtr = m_DefaultBuf;
	m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
	_snprintf(m_StringPtr,m_StringBufSize,"%d",In);
}
//.................................................................................................................................
MString::MString(const unsigned long In)
{
	m_StringPtr = m_DefaultBuf;
	m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
	_snprintf(m_StringPtr,m_StringBufSize,"%d",In);
}
//.................................................................................................................................
MString::MString(const char * In)
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
//.................................................................................................................................
MString::MString(const MString & In)
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
//.................................................................................................................................
MString::~MString()
{
	if ( m_StringPtr != m_DefaultBuf )
	{
		delete [] m_StringPtr;
		m_StringPtr = m_DefaultBuf;
	}
	m_StringBufSize = MSTRING_DEFAULT_BUFSIZE;
}
//.................................................................................................................................
MString & MString::operator =  (const MString & In)
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
//.................................................................................................................................
MString & MString::operator =  (const char * In)
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
//.................................................................................................................................
MString & MString::operator += (const MString & In)
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
//.................................................................................................................................
MString & MString::operator += (const char * In)
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
//.................................................................................................................................
MString   MString::operator +  (const MString & In)
{
	MString							tempstring(m_StringPtr);

	tempstring += In;

	return(tempstring);
}
//.................................................................................................................................
MString   MString::operator +  (const char * In)
{
	MString							tempstring(m_StringPtr);

	tempstring += In;

	return(tempstring);
}
//.................................................................................................................................
MString operator +  (const char * In1,const MString & In2)
{
	MString							tempstring(In1);

	return(tempstring + In2);
}
//.................................................................................................................................
bool   operator == (const MString & In1,const MString & In2)
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
//..............................................................................................................................
bool   operator == (const MString & In1,const char * In2)
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
//..............................................................................................................................
bool   operator == (const char * In1,const MString & In2)
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
//..............................................................................................................................
bool   operator != (const MString & In1,const MString & In2)
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
//..............................................................................................................................
bool   operator != (const MString & In1,const char * In2)
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
//..............................................................................................................................
bool   operator != (const char * In1,const MString & In2)
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
//..............................................................................................................................
bool   operator >  (const MString & In1,const MString & In2)
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
//..............................................................................................................................
bool   operator >  (const MString & In1,const char * In2)
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
//..............................................................................................................................
bool   operator >  (const char * In1,const MString & In2)
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
//..............................................................................................................................
bool   operator >= (const MString & In1,const MString & In2)
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
//..............................................................................................................................
bool   operator >= (const MString & In1,const char * In2)
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
//..............................................................................................................................
bool   operator >= (const char * In1,const MString & In2)
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
//..............................................................................................................................
bool   operator <  (const MString & In1,const MString & In2)
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
//..............................................................................................................................
bool   operator <  (const MString & In1,const char * In2)
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
//..............................................................................................................................
bool   operator <  (const char * In1,const MString & In2)
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
//..............................................................................................................................
bool   operator <= (const MString & In1,const MString & In2)
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
//..............................................................................................................................
bool   operator <= (const MString & In1,const char * In2)
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
//..............................................................................................................................
bool   operator <= (const char * In1,const MString & In2)
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
//.................................................................................................................................
unsigned int MString::Length(void)
{
	return(strlen(m_StringPtr));
}
//.................................................................................................................................
void MString::Upper(void)
{
	#ifdef WINDOWSCODE
		_strupr(m_StringPtr);
	#else
		register int			i;
		
		for ( i=0;i<=strlen(m_StringPtr)-1;i++ )
		{
			if ( m_StringPtr[i] >= 97 && m_StringPtr[i] <= 122 )
			{
				m_StringPtr[i] -= 32;	
			}
		}
	#endif
}
//.................................................................................................................................
void MString::Lower(void)
{
	#ifdef WINDOWSCODE
		_strlwr(m_StringPtr);
	#else
		register int			i;
		
		for ( i=0;i<=strlen(m_StringPtr)-1;i++ )
		{
			if ( m_StringPtr[i] >= 65 && m_StringPtr[i] <= 90 )
			{
				m_StringPtr[i] += 32;	
			}
		}
	#endif
}
//.................................................................................................................................
int  MString::StringPosition(const MString & In)
{
	char					*	tempcharptr;

	if ( (tempcharptr = strstr(m_StringPtr,In.m_StringPtr)) == NULL )
	{
		return(ERROR_MSTRING_NOSUBSTRING);
	}
	else
	{
		return(tempcharptr - m_StringPtr);
	}
}
//.................................................................................................................................
int  MString::StringPosition(const char * In)
{
	char					*	tempcharptr;

	if ( (tempcharptr = strstr(m_StringPtr,In)) == NULL )
	{
		return(ERROR_MSTRING_NOSUBSTRING);
	}
	else
	{
		return(tempcharptr - m_StringPtr);
	}
}
//.................................................................................................................................
char & MString::operator [] (const unsigned short In)
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
//.................................................................................................................................
int  MString::SetAt(const unsigned short In,char CharValue)
{
	assert(In < m_StringBufSize);
	if ( In < m_StringBufSize )
	{
		m_StringPtr[In] = CharValue;
		return(1);
	}
	else
	{
		return(ERROR_MSTRING_INVALIDOFFSET);
	}
}
//.................................................................................................................................
void MString::FormatString(const char * Format,...)
{
	va_list						marker;

	va_start(marker,Format);
	_vsnprintf(m_StringPtr,m_StringBufSize,Format,marker);
	va_end( marker );
}
//.................................................................................................................................
void MString::TrimLeft(void)
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
//.................................................................................................................................
void MString::TrimRight(void)
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
//.................................................................................................................................
char * MString::c_str(void)
{
	return(m_StringPtr);
}
//.................................................................................................................................
void MString::TrimLeft(char * String)
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
//.................................................................................................................................
void MString::TrimRight(char * String)
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
//---------------------------------------------------------------------------------------------------------------------------------


MString MString::basename()
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
	MString tmp(tmpBuf);
	free(tmpBuf);
	return tmp;
}

 MString   MString::dirname()
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
	 MString tmp(tmpBuf);
	free(tmpBuf);
	return tmp;
}

//########################################################################
//用 in 的str 来填充本字符串 是本字符串 达到 length长度。 
MString::MString(const char *in, int length)
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


//########################################################################
std::ostream & operator << ( std::ostream &in , const MString  &in2)
{
	in<<in2.m_StringPtr;
	return in;
}


void MString::Trim()

{
		TrimRight();
		TrimLeft();
}



void MString::Trim(char * String)
{
		MString::TrimRight(String);
		MString::TrimLeft(String);
}

