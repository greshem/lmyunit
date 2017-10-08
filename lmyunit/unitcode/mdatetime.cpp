//--------------------------------------------------------------------------------------------------------------------------------
#include "mdatetime.h"
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MCounter,MObject)

END_LMYUNIT
//................................................................................................................................
MCounter::MCounter(void)
{
	m_RecordData = 0;
}
//................................................................................................................................
MCounter::~MCounter()
{

}
//................................................................................................................................
void MCounter::GetCurTickCount(void)
{

#ifdef WINDOWSCODE
	//Windows版本
	m_RecordData = ::GetTickCount();
#else
	//Linux版本
	struct timeval 		errorcode;
	
	gettimeofday(&errorcode,NULL);
	m_RecordData = errorcode.tv_sec * 1000*1000 + errorcode.tv_usec ;
#endif

}
//................................................................................................................................
unsigned long MCounter::GetDuration(void)
{
#ifdef WINDOWSCODE
	//Windows版本
	return(::GetTickCount() - m_RecordData);
#else
	//Linux版本
	struct timeval 		errorcode;
	
	gettimeofday(&errorcode,NULL);
	return(errorcode.tv_sec * 1000*1000 + errorcode.tv_usec  - m_RecordData);
#endif
}
//................................................................................................................................
MString MCounter::GetDurationString(void)
{
	register unsigned long				errorcode;
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
//................................................................................................................................
bool MCounter::IsEmpty(void)
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
//........................................................................
unsigned long MCounter::GetTickCount()
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
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MDateTime,MObject)

END_LMYUNIT
//................................................................................................................................
MDateTime::MDateTime(void)
{
	m_RecordData = 0;
}
//................................................................................................................................
MDateTime::MDateTime(unsigned short Year,unsigned short Month,unsigned short Day)
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
//................................................................................................................................
MDateTime::MDateTime(unsigned short Hour,unsigned short Min,unsigned short Sec,unsigned short MSec)
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
//................................................................................................................................
MDateTime::MDateTime(unsigned short Year,unsigned short Month,unsigned short Day,unsigned short Hour,unsigned short Min,unsigned short Sec)
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
//................................................................................................................................
MDateTime::MDateTime(unsigned long Date,unsigned long Time)
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
//................................................................................................................................
MDateTime::MDateTime(unsigned long In)
{
	m_RecordData = In;
}
//................................................................................................................................
MDateTime::MDateTime(const MDateTime & In)
{
	m_RecordData = In.m_RecordData;
}
//................................................................................................................................
MDateTime::~MDateTime()
{

}
//................................................................................................................................
void MDateTime::SetCurDateTime(void)
{
	m_RecordData = time(NULL);
}
//........................................................................
void MDateTime::SetDateTime( const char* szDateTime )
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
//................................................................................................................................
MString MDateTime::DateToString(void)
{
	char							tempbuf[256];
	struct tm					*	temptime;

#ifdef WINDOWSCODE
	#if _MSC_VER >= 1400
		if ( (temptime = _localtime64((__time64_t *) &m_RecordData)) == NULL )
	#else
		if ( (temptime = localtime(&m_RecordData)) == NULL )
		//if ( (temptime = localtime(&m_RecordData)) == NULL )
	#endif 
	{
		return("无效时间日期");
	}

	_snprintf(tempbuf,256,"%d-%d-%d",temptime->tm_year + 1900,temptime->tm_mon + 1,temptime->tm_mday);
#else
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
//................................................................................................................................
MString MDateTime::TimeToString(void)
{
	char							tempbuf[256];
	struct tm					*	temptime;

#ifdef WINDOWSCODE

	#if _MSC_VER >= 1400
		if ( (temptime = _localtime64((__time64_t *) &m_RecordData)) == NULL )
	#else
		if ( (temptime = localtime(&m_RecordData)) == NULL )
		//if ( (temptime = localtime(&m_RecordData)) == NULL )
	#endif 
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
//................................................................................................................................
MString MDateTime::DateTimeToString(void)
{
	char							tempbuf[256];
	struct tm					*	temptime;

#ifdef WINDOWSCODE
	#if _MSC_VER >= 1400
		if ( (temptime = _localtime64((__time64_t *) &m_RecordData)) == NULL )
	#else
		if ( (temptime = localtime(&m_RecordData)) == NULL )
		//if ( (temptime = localtime(&m_RecordData)) == NULL )
	#endif 
	{
		return("无效时间日期");
	}

	_snprintf(tempbuf,256,"%04d-%02d-%02d %02d:%02d:%02d",temptime->tm_year + 1900,temptime->tm_mon + 1,temptime->tm_mday,temptime->tm_hour,temptime->tm_min,temptime->tm_sec);
#else
	struct tm						lctime;
	memset( &lctime, 0, sizeof( struct tm ) );
	if ( (temptime = localtime_r(&m_RecordData, &lctime)) == NULL )
	{
		return("无效时间日期");
	}
	
	_snprintf(tempbuf,256,"%04d-%02d-%02d %02d:%02d:%02d",lctime.tm_year + 1900,lctime.tm_mon + 1,lctime.tm_mday,lctime.tm_hour,lctime.tm_min,lctime.tm_sec);
#endif //WINDOWSCODE

	return(tempbuf);
}
//................................................................................................................................
long MDateTime::DateTimeToTimet(void)
{
	return(m_RecordData);	
}
//................................................................................................................................
MString MDateTime::GetDurationString(void)
{
	register unsigned long			errorcode;
	char							tempbuf[256];

	errorcode = time(NULL) - m_RecordData;

	_snprintf(tempbuf,256,"%d:%d:%d",errorcode / 3600,(errorcode % 3600) / 60,errorcode % 60);

	return(tempbuf);
}
//................................................................................................................................
long MDateTime::GetDuration(void)
{
	return(time(NULL) - m_RecordData);
}
//................................................................................................................................
unsigned long MDateTime::DateToLong(void)
{
	struct tm					*	temptime;

#ifdef WINDOWSCODE
	#if _MSC_VER >= 1400
		if ( (temptime = _localtime64((__time64_t *) &m_RecordData)) == NULL )
	#else
		if ( (temptime = localtime(&m_RecordData)) == NULL )
		//if ( (temptime = localtime(&m_RecordData)) == NULL )
	#endif 
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
	if ( (temptime = localtime_r(&m_RecordData, &lctime)) == NULL )
	{
		return(0);
	}
	else
	{
		return((lctime.tm_year + 1900) * 10000 + (lctime.tm_mon + 1) * 100 + lctime.tm_mday);
	}
#endif //WINDOWSCODE
}
//................................................................................................................................
unsigned long MDateTime::TimeToLong(void)
{
	struct tm					*	temptime;

#ifdef WINDOWSCODE
	#if _MSC_VER >= 1400
		if ( (temptime = _localtime64((__time64_t *) &m_RecordData)) == NULL )
	#else
		if ( (temptime = localtime(&m_RecordData)) == NULL )
		//if ( (temptime = localtime(&m_RecordData)) == NULL )
	#endif 
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
	if ( (temptime = localtime_r(&m_RecordData, &lctime)) == NULL )
	{
		return(0);
	}
	else
	{
		return(lctime.tm_hour * 10000 + lctime.tm_min * 100 + lctime.tm_sec);
	}
#endif //WINDOWSCODE
}
//................................................................................................................................
MDateTime & MDateTime::operator = (const MDateTime & In)
{
	m_RecordData = In.m_RecordData;

	return(* this);
}
//................................................................................................................................
MDateTime MDateTime::operator - (MDateTime & In)
{
	return(MDateTime(m_RecordData - In.m_RecordData));
}
//................................................................................................................................
int  MDateTime::GetDayOfWork(void)
{
	struct tm					*	temptime;

#ifdef WINDOWSCODE
	#if _MSC_VER >= 1400
		if ( (temptime = _localtime64((__time64_t *) &m_RecordData)) == NULL )
	#else
		if ( (temptime = localtime(&m_RecordData)) == NULL )
		//if ( (temptime = localtime(&m_RecordData)) == NULL )
	#endif 
	{
		return(ERROR_MDATETIME_INVALID);
	}

	return(temptime->tm_wday);
#else
	struct tm						lctime;
	memset( &lctime, 0, sizeof( struct tm ));
	if ( (temptime = localtime_r(&m_RecordData, &lctime)) == NULL )
	{
		return(ERROR_MDATETIME_INVALID);
	}
	
	return(lctime.tm_wday);
#endif //WINDOWSCODE
}
//................................................................................................................................
int  MDateTime::GetDayOfYear(void)
{
	struct tm					*	temptime;

#ifdef WINDOWSCODE
	#if _MSC_VER >= 1400
		if ( (temptime = _localtime64((__time64_t *) &m_RecordData)) == NULL )
	#else
		if ( (temptime = localtime(&m_RecordData)) == NULL )
		//if ( (temptime = localtime(&m_RecordData)) == NULL )
	#endif 
	{
		return(ERROR_MDATETIME_INVALID);
	}

	return(temptime->tm_yday);
#else
	struct tm						lctime;
	memset( &lctime, 0, sizeof( struct tm) );
	if ( (temptime = localtime_r(&m_RecordData, &lctime)) == NULL )
	{
		return(ERROR_MDATETIME_INVALID);
	}
	
	return(lctime.tm_yday);
#endif //WINDOWSCODE
}
//................................................................................................................................
MDateTime MDateTime::operator + (unsigned long In)
{
	return(MDateTime(m_RecordData + In));
}
//................................................................................................................................
MDateTime & MDateTime::operator += (unsigned long In)
{
	m_RecordData += In;

	return(* this);
}
//................................................................................................................................
void MDateTime::DecodeDate(unsigned short * year,unsigned short * month,unsigned short * day)
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

	#if _MSC_VER >= 1400
		if ( (temptime = _localtime64((__time64_t *) &m_RecordData)) == NULL )
	#else
		if ( (temptime = localtime(&m_RecordData)) == NULL )
		//if ( (temptime = localtime(&m_RecordData)) == NULL )
	#endif 
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
//................................................................................................................................
void MDateTime::DecodeTime(unsigned short * hour,unsigned short * min,unsigned short * sec)
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
	#if _MSC_VER >= 1400
		if ( (temptime = _localtime64((__time64_t *) &m_RecordData)) == NULL )
	#else
		if ( (temptime = localtime(&m_RecordData)) == NULL )
		//if ( (temptime = localtime(&m_RecordData)) == NULL )
	#endif 
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
//................................................................................................................................
bool MDateTime::operator == (const MDateTime & In) const
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
//................................................................................................................................
bool MDateTime::operator != (const MDateTime & In) const
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
//................................................................................................................................
MDateTime MDateTime::Now(void)
{
	return(MDateTime((unsigned long)time(NULL)));
}
//--------------------------------------------------------------------------------------------------------------------------------
