//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMDateTimeH__
#define __LmyUnitMDateTimeH__
//--------------------------------------------------------------------------------------------------------------------------------
//公共头文件
#include "mobject.h"
//................................................................................................................................
#ifdef WINDOWSCODE
//................................................................................................................................
//Windows操作系统
//................................................................................................................................
#else
//................................................................................................................................
//Linux操作系统
#include <sys/time.h>
//................................................................................................................................
#endif
//--------------------------------------------------------------------------------------------------------------------------------
class MCounter : public MObject
{
protected:
    
 #if _MSC_VER >= 1400
	long long 						m_RecordData;
 #else
	unsigned long					m_RecordData;
 #endif 

public:
	MCounter(void);
	virtual ~MCounter();
public:
	void GetCurTickCount(void);
	unsigned long GetDuration(void);
	MString GetDurationString(void);
	bool IsEmpty(void);
	static unsigned long GetTickCount();

	DECLARE_LMYUNIT(MCounter)
};
//--------------------------------------------------------------------------------------------------------------------------------
#define		ERROR_MDATETIME_INVALID		ERROR_USER(20)		//无效的日期时间
//................................................................................................................................
class MDateTime : public MObject
{
protected:
	long							m_RecordData;
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
	MString DateToString(void);
	MString TimeToString(void);
	MString DateTimeToString(void);
	long DateTimeToTimet(void);
public:
	unsigned long DateToLong(void);
	unsigned long TimeToLong(void);
public:
	MDateTime & operator = (const MDateTime & In);
	MDateTime operator - (MDateTime & In);
	MDateTime operator + (unsigned long In);
	MDateTime & operator += (unsigned long In);
public:
	MString GetDurationString(void);
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

	DECLARE_LMYUNIT(MDateTime)
};
//--------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------
