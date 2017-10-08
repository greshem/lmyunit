//#####################################################################################
//#####################################################################################
#ifndef __LmyUnitMDateTimeH__
#define __LmyUnitMDateTimeH__
//#####################################################################################
//公共头文件
//#include "MObject.h"
#include "MString.hpp"
//#####################################################################################
#ifdef WINDOWSCODE
//#####################################################################################
//Windows操作系统
//#####################################################################################
#else
//#####################################################################################
//Linux操作系统
#include <sys/time.h>
//#####################################################################################
#endif
//#####################################################################################
template <typename T>class  MCounter
{
protected:
 #if _MSC_VER >= 1400
	long long m_RecordData;
 #else
	unsigned long					m_RecordData;
	//unsigned long long 				m_RecordData;
 #endif 

public:
	MCounter(void);
	virtual ~MCounter();
public:
	void GetCurTickCount(void);
	unsigned long GetDuration(void);
	MString<char> GetDurationString(void);
	bool IsEmpty(void);
	static unsigned long GetTickCount();

//	DECLARE_LMYUNIT(MCounter)
};
//#####################################################################################
#define		ERROR_MDATETIME_INVALID		ERROR_USER(20)		//无效的日期时间
//#####################################################################################
template <typename T>class  MDateTime //: public MObject
{
protected:


protected:
 #if _MSC_VER >= 1400
	long long m_RecordData;
 #else
	unsigned long					m_RecordData;
	//unsigned long long 					m_RecordData;
 #endif 

public:
	MDateTime(void);
	MDateTime(unsigned short Year,unsigned short Month,unsigned short Day);
	MDateTime(unsigned short Hour,unsigned short Min,unsigned short Sec,unsigned short MSec);
	MDateTime(unsigned short Year,unsigned short Month,unsigned short Day,unsigned short Hour,unsigned short Min,unsigned short Sec);
	MDateTime(unsigned long Date,unsigned long Time);
	MDateTime(unsigned long In);
	MDateTime(const MDateTime & In);
	virtual ~MDateTime();
public:
	void SetCurDateTime(void);
	void SetDateTime( const char* szDateTime );
public:
	MString<T> DateToString(void);
	MString<T> TimeToString(void);
	MString<T> DateTimeToString(void);
	long DateTimeToTimet(void);
public:
	unsigned long DateToLong(void);
	unsigned long TimeToLong(void);
public:
	MDateTime<T> & operator = (const MDateTime & In);
	MDateTime<T> operator - (MDateTime & In);
	MDateTime<T> operator + (unsigned long In);
	MDateTime<T> & operator += (unsigned long In);
public:
	MString<T> GetDurationString(void);
	long GetDuration(void);
public:
	int  GetDayOfWork(void);
	int  GetDayOfYear(void);
public:
	void DecodeDate(unsigned short * year,unsigned short * month,unsigned short * day);
	void DecodeTime(unsigned short * hour,unsigned short * min,unsigned short * sec);
public:
	bool operator == (const MDateTime & In) const;
	bool operator != (const MDateTime & In) const;
public:
	static MDateTime Now(void);

//	DECLARE_LMYUNIT(MDateTime)
};
//#####################################################################################

//#####################################################################################
//#####################################################################################
//#include "iostream"
//#####################################################################################
//BEGIN_LMYUNIT(MCounter,MObject)

//END_LMYUNITEND_LMYUNIT
//#####################################################################################
template <typename T> MCounter<T>::MCounter(void)
{
	m_RecordData = 0;
}
//#####################################################################################
 template <typename T> MCounter<T>::~MCounter()
{

}
//#####################################################################################
 template <typename T> void MCounter<T>::GetCurTickCount(void)
{

#ifdef WINDOWSCODE
	//Windows版本
	m_RecordData = ::GetTickCount();
#else
	//Linux版本
	struct timeval 		errorcode;
	
	gettimeofday(&errorcode,NULL);
	m_RecordData = errorcode.tv_sec * 1000 + errorcode.tv_usec / 1000;
#endif

}
//#####################################################################################
 template <typename T> unsigned long MCounter<T>::GetDuration(void)
{
#ifdef WINDOWSCODE
	//Windows版本
	return(::GetTickCount() - m_RecordData);
#else
	//Linux版本
	struct timeval 		errorcode;
	
	gettimeofday(&errorcode,NULL);
	return(errorcode.tv_sec * 1000 + errorcode.tv_usec / 1000 - m_RecordData);
#endif
}
//#####################################################################################
template <typename T> MString<char>  MCounter<T>::GetDurationString(void)
{
	//register unsigned long				errorcode;
	register int 				errorcode;
	char								tempbuf[256];

#ifdef WINDOWSCODE
	//Windows版本
	errorcode = ::GetTickCount() - m_RecordData;
#else
	//Linux版本
	errorcode = GetDuration();
#endif

	_snprintf(tempbuf,256,"%d:%d:%d",errorcode / 3600,(errorcode % 3600) / 60,errorcode % 60);

	return(tempbuf);
}
//#####################################################################################
 template <typename T> bool MCounter<T>::IsEmpty(void)
{
	if ( m_RecordData == 0 )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//#####################################################################################
 template <typename T> unsigned long MCounter<T>::GetTickCount()
{
#ifdef WINDOWSCODE
	//Windows版本
	return (::GetTickCount());
#else
	//Linux版本
	struct timeval 		errorcode;
	
	gettimeofday(&errorcode,NULL);
	return ( errorcode.tv_sec * 1000 + errorcode.tv_usec / 1000 );
#endif
}
//#####################################################################################
//BEGIN_LMYUNIT(MDateTime,MObject)

//END_LMYUNITEND_LMYUNIT
//#####################################################################################
  template <typename T>MDateTime<T>::MDateTime(void)
{
	m_RecordData = 0;
}
//#####################################################################################
  template <typename T>MDateTime<T>::MDateTime(unsigned short Year,unsigned short Month,unsigned short Day)
{
	struct tm						temptime;

	temptime.tm_year = Year - 1900;
	temptime.tm_mon = Month - 1;
	temptime.tm_mday = Day;
	temptime.tm_hour = 0;  
	temptime.tm_min = 0;
	temptime.tm_sec = 0;
	m_RecordData = mktime(&temptime);
	assert(m_RecordData != -1);
}
//#####################################################################################
  template <typename T>MDateTime<T>::MDateTime(unsigned short Hour,unsigned short Min,unsigned short Sec,unsigned short MSec)
{
	struct tm						temptime;

	temptime.tm_year = 70;
	temptime.tm_mon = 0;
	temptime.tm_mday = 1;
	temptime.tm_hour = Hour;  
	temptime.tm_min = Min;
	temptime.tm_sec = Sec;
	m_RecordData = mktime(&temptime);
	assert(m_RecordData != -1);
}
//#####################################################################################
  template <typename T>MDateTime<T>::MDateTime(unsigned short Year,unsigned short Month,unsigned short Day,unsigned short Hour,unsigned short Min,unsigned short Sec)
{
	struct tm						temptime;

	temptime.tm_year = Year - 1900;
	temptime.tm_mon = Month - 1;
	temptime.tm_mday = Day;
	temptime.tm_hour = Hour;  
	temptime.tm_min = Min;
	temptime.tm_sec = Sec;

	m_RecordData = mktime(&temptime);
	assert(m_RecordData != -1);
}
//#####################################################################################
  template <typename T>MDateTime<T>::MDateTime(unsigned long Date,unsigned long Time)
{
	struct tm						temptime;

	temptime.tm_year = (Date / 10000) - 1900;
	temptime.tm_mon = (Date % 10000) / 100 - 1;
	temptime.tm_mday = Date % 100;
	temptime.tm_hour = Time / 10000;
	temptime.tm_min = (Time % 10000) / 100;
	temptime.tm_sec = Time % 100;
	m_RecordData = mktime(&temptime);
	assert(m_RecordData != -1);
}
//#####################################################################################
  template <typename T> MDateTime<T>::MDateTime(unsigned long In)
{
	m_RecordData = In;
}
//#####################################################################################
  template <typename T> MDateTime<T>::MDateTime(const MDateTime & In)
{
	m_RecordData = In.m_RecordData;
}
//#####################################################################################
  template <typename T> MDateTime<T>::~MDateTime()
{

}
//#####################################################################################
  template <typename T> void MDateTime<T>::SetCurDateTime(void)
{
	m_RecordData = time(NULL);
}
//#####################################################################################
  template <typename T> void MDateTime<T>::SetDateTime( const char* szDateTime )
{//字符串必须形如"1980-03-14 18:01:02"
	int year,month,day,hour,min,sec;
	sscanf( szDateTime, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &min, &sec );
	
	struct tm						temptime;
	memset( &temptime, 0, sizeof( tm) );
	temptime.tm_year = year- 1900;
	temptime.tm_mon = month - 1;
	temptime.tm_mday = day;
	temptime.tm_hour = hour;  
	temptime.tm_min = min;
	temptime.tm_sec = sec;
	
	m_RecordData = mktime(&temptime);
	assert(m_RecordData != -1);
}
//#####################################################################################
  template <typename T> MString<T> MDateTime<T>::DateToString(void)
{
	char							tempbuf[256];
	struct tm					*	temptime;

#ifdef WINDOWSCODE
	if ( (temptime = localtime(&m_RecordData)) == NULL )
	{
		return("无效时间日期");
	}

	_snprintf(tempbuf,256,"%d-%d-%d",temptime->tm_year + 1900,temptime->tm_mon + 1,temptime->tm_mday);
#else
	memset(tempbuf, '\0', sizeof(tempbuf));
	struct tm						lctime;
	memset( &lctime, 0, sizeof(struct tm) );
	if ( (temptime = localtime_r(&m_RecordData, &lctime)) == NULL )
	{
		return("无效时间日期");
	}
	
	_snprintf(tempbuf,256,"%d-%d-%d",lctime.tm_year + 1900,lctime.tm_mon + 1,lctime.tm_mday);
#endif //WINDOWSCODE
	return(tempbuf);
}
//#####################################################################################
  template <typename T> MString<T> MDateTime<T>::TimeToString(void)
{
	char							tempbuf[256];
	struct tm					*	temptime;

#ifdef WINDOWSCODE
	if ( (temptime = localtime(&m_RecordData)) == NULL )
	{
		return("无效时间日期");
	}

	_snprintf(tempbuf,256,"%d:%d:%d",temptime->tm_hour,temptime->tm_min,temptime->tm_sec);
#else
	struct tm						lctime;
	memset( &lctime, 0, sizeof( struct tm) );
	if ( (temptime = localtime_r(&m_RecordData, &lctime)) == NULL )
	{
		return("无效时间日期");
	}
	
	_snprintf(tempbuf,256,"%d:%d:%d",lctime.tm_hour,lctime.tm_min,lctime.tm_sec);
#endif //WINDOWSCODE

	return(tempbuf);
}
//#####################################################################################
  template <typename T> MString<T> MDateTime<T>::DateTimeToString(void)
{
	char							tempbuf[256];
	struct tm					*	temptime;

#ifdef WINDOWSCODE

 #if _MSC_VER >= 1400
	if ( (temptime = _localtime64( &m_RecordData)) == NULL )
 #else
	if ( (temptime = localtime(&m_RecordData)) == NULL )
 #endif 
	{
		return("无效时间日期");
	}

	_snprintf(tempbuf,256,"%04d-%02d-%02d %02d:%02d:%02d",temptime->tm_year + 1900,temptime->tm_mon + 1,temptime->tm_mday,temptime->tm_hour,temptime->tm_min,temptime->tm_sec);
#else
	struct tm						lctime;
	memset( &lctime, 0, sizeof( struct tm ) );
	if ( (temptime = localtime_r((time_t*)&m_RecordData, &lctime)) == NULL )
	{
		return("无效时间日期");
	}
	
	_snprintf(tempbuf,256,"%04d-%02d-%02d %02d:%02d:%02d",lctime.tm_year + 1900,lctime.tm_mon + 1,lctime.tm_mday,lctime.tm_hour,lctime.tm_min,lctime.tm_sec);
#endif //WINDOWSCODE

	return(tempbuf);
}
//#####################################################################################
  template <typename T> long MDateTime<T>::DateTimeToTimet(void)
{
	return(m_RecordData);	
}
//#####################################################################################
  template <typename T> MString<T> MDateTime<T>::GetDurationString(void)
{
	register int 			errorcode;
	char							tempbuf[256];

	errorcode = time(NULL) - m_RecordData;

	_snprintf(tempbuf,256,"%d:%d:%d",errorcode / 3600,(errorcode % 3600) / 60,errorcode % 60);

	return(tempbuf);
}
//#####################################################################################
  template <typename T>long MDateTime<T>::GetDuration(void)
{
	return(time(NULL) - m_RecordData);
}
//#####################################################################################
  template <typename T> unsigned long MDateTime<T>::DateToLong(void)
{
	struct tm					*	temptime;

#ifdef WINDOWSCODE
	if ( (temptime = localtime(&m_RecordData)) == NULL )
	{
		return(0);
	}
	else
	{
		return((temptime->tm_year + 1900) * 10000 + (temptime->tm_mon + 1) * 100 + temptime->tm_mday);
	}
#else
	struct tm						lctime;
	memset( &lctime, 0, sizeof( struct tm) );
	if ( (temptime = localtime_r((time_t *)&m_RecordData, &lctime)) == NULL )
	{
		return(0);
	}
	else
	{
		return((lctime.tm_year + 1900) * 10000 + (lctime.tm_mon + 1) * 100 + lctime.tm_mday);
	}
#endif //WINDOWSCODE
}
//#####################################################################################
  template <typename T> unsigned long MDateTime<T>::TimeToLong(void)
{
	struct tm					*	temptime;

#ifdef WINDOWSCODE
	if ( (temptime = localtime(&m_RecordData)) == NULL )
	{
		return(0);
	}
	else
	{
		return(temptime->tm_hour * 10000 + temptime->tm_min * 100 + temptime->tm_sec);
	}
#else
	struct tm						lctime;
	memset( &lctime, 0, sizeof( struct tm) );
	if ( (temptime = localtime_r((time_t *)&m_RecordData, &lctime)) == NULL )
	{
		return(0);
	}
	else
	{
		return(lctime.tm_hour * 10000 + lctime.tm_min * 100 + lctime.tm_sec);
	}
#endif //WINDOWSCODE
}
//#####################################################################################
  template <typename T> MDateTime<T> & MDateTime<T>::operator = (const MDateTime & In)
{
	m_RecordData = In.m_RecordData;

	return(* this);
}
//#####################################################################################
  template <typename T> MDateTime<T> MDateTime<T>::operator - (MDateTime & In)
{
	return(MDateTime(m_RecordData - In.m_RecordData));
}
//#####################################################################################
  template <typename T> int  MDateTime<T>::GetDayOfWork(void)
{
	struct tm					*	temptime;

#ifdef WINDOWSCODE
	if ( (temptime = localtime(&m_RecordData)) == NULL )
	{
//		return(ERROR_MDATETIME_INVALID);
		return -1;
	}

	return(temptime->tm_wday);
#else
	struct tm						lctime;
	memset( &lctime, 0, sizeof( struct tm ));
	if ( (temptime = localtime_r(&m_RecordData, &lctime)) == NULL )
	{
		//return(ERROR_MDATETIME_INVALID);
		return -1;
	}
	
	return(lctime.tm_wday);
#endif //WINDOWSCODE
}
//#####################################################################################
  template <typename T> int  MDateTime<T>::GetDayOfYear(void)
{
	struct tm					*	temptime;

#ifdef WINDOWSCODE
	if ( (temptime = localtime(&m_RecordData)) == NULL )
	{
		//return(ERROR_MDATETIME_INVALID);
		return -1;
	}

	return(temptime->tm_yday);
#else
	struct tm						lctime;
	memset( &lctime, 0, sizeof( struct tm) );
	if ( (temptime = localtime_r(&m_RecordData, &lctime)) == NULL )
	{
	//	return(ERROR_MDATETIME_INVALID);
		return -1;
	}
	
	return(lctime.tm_yday);
#endif //WINDOWSCODE
}
//#####################################################################################
  template <typename T>MDateTime<T> MDateTime<T>::operator + (unsigned long In)
{
	return(MDateTime(m_RecordData + In));
}
//#####################################################################################
  template <typename T>MDateTime<T> & MDateTime<T>::operator += (unsigned long In)
{
	m_RecordData += In;

	return(* this);
}
//#####################################################################################
  template <typename T>void MDateTime<T>::DecodeDate(unsigned short * year,unsigned short * month,unsigned short * day)
{
	/*
	struct tm						*	temptime;

	temptime = gmtime(&m_RecordData);
	assert(temptime != NULL);
	if ( temptime != NULL )
	{
		* year = temptime->tm_year + 1900;
		* month = temptime->tm_mon + 1;
		* day = temptime->tm_mday;
	}
	else
	{
		* year = 0;
		* month = 0;
		* day = 0;
	}
	*/
	struct tm					*	temptime;
	
#ifdef WINDOWSCODE
	if ( (temptime = localtime(&m_RecordData)) == NULL )
	{
		* year = 0;
		* month = 0;
		* day = 0;
	}
	else
	{
		* year = temptime->tm_year + 1900;
		* month = temptime->tm_mon + 1;
		* day = temptime->tm_mday;	
	}
#else
	struct tm						lctime;
	memset( &lctime, 0, sizeof( struct tm) );
	if ( (temptime = localtime_r(&m_RecordData, &lctime)) == NULL )
	{
		* year = 0;
		* month = 0;
		* day = 0;
	}
	else
	{
		* year = temptime->tm_year + 1900;
		* month = temptime->tm_mon + 1;
		* day = temptime->tm_mday;	
	}
#endif //WINDOWSCODE
}
//#####################################################################################
  template <typename T>void MDateTime<T>::DecodeTime(unsigned short * hour,unsigned short * min,unsigned short * sec)
{
/*
	struct tm						*	temptime;

	temptime = gmtime(&m_RecordData);
	assert(temptime != NULL);
	if ( temptime != NULL )
	{
		* hour = temptime->tm_hour;
		* min = temptime->tm_min;
		* sec = temptime->tm_sec;
	}
	else
	{
		* hour = 0;
		* min = 0;
		* sec = 0;
	}
*/
	struct tm					*	temptime;
	
#ifdef WINDOWSCODE
	if ( (temptime = localtime(&m_RecordData)) == NULL )
	{
		* hour = 0;
		* min = 0;
		* sec = 0;
	}
	else
	{
		* hour = temptime->tm_hour;
		* min = temptime->tm_min;
		* sec = temptime->tm_sec;
	}
#else
	struct tm						lctime;
	memset( &lctime, 0, sizeof( struct tm) );
	if ( (temptime = localtime_r(&m_RecordData, &lctime)) == NULL )
	{
		* hour = 0;
		* min = 0;
		* sec = 0;
	}
	else
	{
		* hour = temptime->tm_hour;
		* min = temptime->tm_min;
		* sec = temptime->tm_sec;
	}
#endif //WINDOWSCODE
}
//#####################################################################################
  template <typename T>bool MDateTime<T>::operator == (const MDateTime & In) const
{
	if ( m_RecordData == In.m_RecordData )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//#####################################################################################
  template <typename T> bool MDateTime<T>::operator != (const MDateTime & In) const
{
	if ( m_RecordData != In.m_RecordData )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//#####################################################################################
  template <typename T>MDateTime<T> MDateTime<T>::Now(void)
{
	return(MDateTime<T>((unsigned long)time(NULL)));
}
//#####################################################################################
/*using namespace std;
main()
{
      MDateTime time;
   //   std::cout <<"time"<<endl;
    time.SetCurDateTime();
    printf("%s\n", time.TimeToString().c_str());
    printf("%s\n", time.DateTimeToString().c_str());
    getchar();
}*/
#endif
