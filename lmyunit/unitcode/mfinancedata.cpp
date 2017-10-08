//--------------------------------------------------------------------------------------------------------------------------
#include "mfinancedata.h"
//--------------------------------------------------------------------------------------------------------------------------
#define		PutBit(value,bitsize)	inner_putbit(BitOffset,value,bitsize)
#define		PutBit64(value,bitsize)	inner_putbit64(BitOffset,value,bitsize)
#define		PutBitString(value,bitsize)	inner_putbitstring(BitOffset,value,bitsize)
#define		GetBit(value,bitsize)	inner_getbit(BitOffset,value,bitsize)
#define		GetBit64(value,bitsize)	inner_getbit64(BitOffset,value,bitsize)
#define		GetBitString(value,bitsize)	inner_getbitstring(BitOffset,value,bitsize)
//..........................................................................................................................
MFinanceBaseData::MFinanceBaseData(void)
{
	m_RecordData = NULL;
	m_MaxBitSize = 0;

	memset(m_DefaultBuf,0x00,16);
	m_Value = m_DefaultBuf;
	m_MaxValueSize = 16;
}
//..........................................................................................................................
MFinanceBaseData::~MFinanceBaseData()
{
	m_RecordData = NULL;
	m_MaxBitSize = 0;

	if ( m_Value != m_DefaultBuf )
	{
		delete [] m_Value;
		m_Value = m_DefaultBuf;
	}
	m_MaxValueSize = 16;
}
//..........................................................................................................................
void MFinanceBaseData::AttchBuf(char * InBuf,unsigned long InSize)
{
	m_RecordData = InBuf;
	m_MaxBitSize = InSize;
}
//..........................................................................................................................
void MFinanceBaseData::WriteDataToBuf(unsigned long * BitOffset)
{
	
}
//..........................................................................................................................
void MFinanceBaseData::ReadDataFromBuf(unsigned long * BitOffset)
{

}
//..........................................................................................................................
int  MFinanceBaseData::ReadDefaultData(unsigned long * Offset)
{
	return(1);
}
//..........................................................................................................................
int  MFinanceBaseData::WriteDefaultData(char * InBuf,unsigned long * Offset)
{
	return(1);
}
//--------------------------------------------------------------------------------------------------------------------------
MFD_MarketID::MFD_MarketID(void)
{

}
//..........................................................................................................................
MFD_MarketID::~MFD_MarketID()
{

}
//..........................................................................................................................
void MFD_MarketID::WriteDataToBuf(unsigned long * BitOffset)
{
	unsigned long				errorcode = GetData();

	if ( errorcode < ((unsigned long)1 << 3) )
	{
		PutBit(0,1);
		PutBit(errorcode,3);
	}
	else
	{
		PutBit(1,1);
		PutBit(errorcode,8);
	}
}
//..........................................................................................................................
void MFD_MarketID::ReadDataFromBuf(unsigned long * BitOffset)
{
	unsigned long				errorcode = 0;

	GetBit(&errorcode,1);
	if ( errorcode == 0 )
	{
		GetBit(&errorcode,3);
	}
	else
	{
		GetBit(&errorcode,8);
	}

	SetData((unsigned char)errorcode);
}
//--------------------------------------------------------------------------------------------------------------------------
MFD_WareType::MFD_WareType(void)
{
	
}
//..........................................................................................................................
MFD_WareType::~MFD_WareType()
{
	
}
//..........................................................................................................................
void MFD_WareType::WriteDataToBuf(unsigned long * BitOffset)
{
	unsigned long				errorcode = GetData();
	
	if ( errorcode < ((unsigned long)1 << 4) )
	{
		PutBit(0,1);
		PutBit(errorcode,4);
	}
	else
	{
		PutBit(1,1);
		PutBit(errorcode,8);
	}
}
//..........................................................................................................................
void MFD_WareType::ReadDataFromBuf(unsigned long * BitOffset)
{
	unsigned long				errorcode = 0;
	
	GetBit(&errorcode,1);
	if ( errorcode == 0 )
	{
		GetBit(&errorcode,4);
	}
	else
	{
		GetBit(&errorcode,8);
	}
	
	SetData((unsigned char)errorcode);
}
//--------------------------------------------------------------------------------------------------------------------------
MFD_TimeZoom::MFD_TimeZoom(void)
{
	
}
//..........................................................................................................................
MFD_TimeZoom::~MFD_TimeZoom()
{
	
}
//..........................................................................................................................
void MFD_TimeZoom::WriteDataToBuf(unsigned long * BitOffset)
{
	long					errorcode = GetData();

	assert(errorcode >= -15 && errorcode <= 15);
	
	if ( errorcode >= 0 )
	{
		PutBit(0,1);
		PutBit(errorcode,4);
	}
	else
	{
		errorcode = (-1) * errorcode;

		PutBit(1,1);
		PutBit(errorcode,4);
	}
}
//..........................................................................................................................
void MFD_TimeZoom::ReadDataFromBuf(unsigned long * BitOffset)
{
	unsigned long				errorcode = 0;
	
	GetBit(&errorcode,1);
	if ( errorcode == 0 )
	{
		GetBit(&errorcode,4);
		SetData((char)errorcode);
	}
	else
	{
		GetBit(&errorcode,4);
		SetData((char)((-1) * (long)errorcode));
	}
}
//--------------------------------------------------------------------------------------------------------------------------
MFD_WareSerial::MFD_WareSerial(void)
{
	
}
//..........................................................................................................................
MFD_WareSerial::~MFD_WareSerial()
{
	
}
//..........................................................................................................................
void MFD_WareSerial::WriteDataToBuf(unsigned long * BitOffset)
{
	long					errorcode = GetData();

	assert(errorcode >= 0 && errorcode <= ((unsigned long)1 << 16));
	
	if ( errorcode < ((unsigned long)1 << 9) )
	{
		PutBit(0,1);
		PutBit(errorcode,9);
	}
	else if ( errorcode < ((unsigned long)1 << 11) )
	{
		PutBit(2,2);
		PutBit(errorcode,11);
	}
	else
	{
		PutBit(3,2);
		PutBit(errorcode,16);
	}
}
//..........................................................................................................................
void MFD_WareSerial::ReadDataFromBuf(unsigned long * BitOffset)
{
	unsigned long				errorcode = 0;
	
	GetBit(&errorcode,1);
	if ( errorcode == 0 )
	{
		GetBit(&errorcode,9);
	}
	else
	{
		GetBit(&errorcode,1);
		if ( errorcode == 0 )
		{
			GetBit(&errorcode,11);
		}
		else
		{
			GetBit(&errorcode,16);
		}
	}
	
	SetData((unsigned short)errorcode);
}
//--------------------------------------------------------------------------------------------------------------------------
MFD_Price::MFD_Price(void)
{
	
}
//..........................................................................................................................
MFD_Price::~MFD_Price()
{
	
}
//..........................................................................................................................
void MFD_Price::WriteDataToBuf(unsigned long * BitOffset)
{
	unsigned long				errorcode = GetData();
	
	if ( errorcode < ((unsigned long)1 << 10) )
	{
		PutBit(0,2);
		PutBit(errorcode,10);
	}
	else if ( errorcode < ((unsigned long)1 << 14) )
	{
		PutBit(1,2);
		PutBit(errorcode,14);
	}
	else if ( errorcode < ((unsigned long)1 << 22) )
	{
		PutBit(2,2);
		PutBit(errorcode,22);
	}
	else
	{
		PutBit(3,2);
		PutBit(errorcode,32);
	}
}
//..........................................................................................................................
void MFD_Price::ReadDataFromBuf(unsigned long * BitOffset)
{
	unsigned long				errorcode = 0;
	
	GetBit(&errorcode,2);
	if ( errorcode == 0 )
	{
		GetBit(&errorcode,10);
	}
	else if ( errorcode == 1 )
	{
		GetBit(&errorcode,14);
	}
	else if ( errorcode == 2 )
	{
		GetBit(&errorcode,22);
	}
	else
	{
		GetBit(&errorcode,32);
	}
	
	SetData(errorcode);
}
//--------------------------------------------------------------------------------------------------------------------------
MFD_SubPrice::MFD_SubPrice(void)
{
	
}
//..........................................................................................................................
MFD_SubPrice::~MFD_SubPrice()
{
	
}
//..........................................................................................................................
void MFD_SubPrice::WriteDataToBuf(unsigned long * BitOffset)
{
	unsigned long				errorcode = GetData();
	
	if ( errorcode < ((unsigned long)1 << 3) )
	{
		PutBit(0,2);
		PutBit(errorcode,3);
	}
	else if ( errorcode < ((unsigned long)1 << 8) )
	{
		PutBit(1,2);
		PutBit(errorcode,8);
	}
	else if ( errorcode < ((unsigned long)1 << 16) )
	{
		PutBit(2,2);
		PutBit(errorcode,16);
	}
	else
	{
		PutBit(3,2);
		PutBit(errorcode,32);
	}
}
//..........................................................................................................................
void MFD_SubPrice::ReadDataFromBuf(unsigned long * BitOffset)
{
	unsigned long				errorcode = 0;
	
	GetBit(&errorcode,2);
	if ( errorcode == 0 )
	{
		GetBit(&errorcode,3);
	}
	else if ( errorcode == 1 )
	{
		GetBit(&errorcode,8);
	}
	else if ( errorcode == 2 )
	{
		GetBit(&errorcode,16);
	}
	else
	{
		GetBit(&errorcode,32);
	}
	
	SetData(errorcode);
}
//--------------------------------------------------------------------------------------------------------------------------
MFD_SignSubPrice::MFD_SignSubPrice(void)
{
	
}
//..........................................................................................................................
MFD_SignSubPrice::~MFD_SignSubPrice()
{
	
}
//..........................................................................................................................
void MFD_SignSubPrice::WriteDataToBuf(unsigned long * BitOffset)
{
	long						errorcode = GetData();

	if ( errorcode >= 0 )
	{
		PutBit(0,1);
	}
	else
	{
		PutBit(1,1);
		errorcode = (-1) * errorcode;
	}
	
	if ( errorcode < ((unsigned long)1 << 3) )
	{
		PutBit(0,2);
		PutBit(errorcode,3);
	}
	else if ( errorcode < ((unsigned long)1 << 8) )
	{
		PutBit(1,2);
		PutBit(errorcode,8);
	}
	else if ( errorcode < ((unsigned long)1 << 16) )
	{
		PutBit(2,2);
		PutBit(errorcode,16);
	}
	else
	{
		PutBit(3,2);
		PutBit(errorcode,32);
	}
}
//..........................................................................................................................
void MFD_SignSubPrice::ReadDataFromBuf(unsigned long * BitOffset)
{
	unsigned long					errorcode;
	register int					sign;
	
	GetBit(&errorcode,1);
	if ( errorcode == 0 )
	{
		sign = 1;
	}
	else
	{
		sign = -1;
	}
	
	GetBit(&errorcode,2);
	if ( errorcode == 0 )
	{
		GetBit(&errorcode,3);
	}
	else if ( errorcode == 1 )
	{
		GetBit(&errorcode,8);
	}
	else if ( errorcode == 2 )
	{
		GetBit(&errorcode,16);
	}
	else
	{
		GetBit(&errorcode,32);
	}
	
	SetData(sign * errorcode);
}
//--------------------------------------------------------------------------------------------------------------------------
MFD_TotalVolume::MFD_TotalVolume(void)
{
	
}
//..........................................................................................................................
MFD_TotalVolume::~MFD_TotalVolume()
{
	
}
//..........................................................................................................................
void MFD_TotalVolume::WriteDataToBuf(unsigned long * BitOffset)
{
	__int64					errorcode = (__int64)(GetData() + 0.5);

	assert(errorcode >= 0 && errorcode <= ((__int64)1 << 40));
	
	if ( errorcode < ((__int64)1 << 10) )
	{
		PutBit(0,2);
		PutBit64(errorcode,10);
	}
	else if ( errorcode < ((__int64)1 << 14) )
	{
		PutBit(1,2);
		PutBit64(errorcode,14);
	}
	else if ( errorcode < ((__int64)1 << 18) )
	{
		PutBit(2,2);
		PutBit64(errorcode,18);
	}
	else if ( errorcode < ((__int64)1 << 22) )
	{
		PutBit(12,4);
		PutBit64(errorcode,22);
	}
	else if ( errorcode < ((__int64)1 << 26) )
	{
		PutBit(13,4);
		PutBit64(errorcode,26);
	}
	else if ( errorcode < ((__int64)1 << 30) )
	{
		PutBit(14,4);
		PutBit64(errorcode,30);
	}
	else
	{
		PutBit(15,4);
		PutBit64(errorcode,40);
	}
}
//..........................................................................................................................
void MFD_TotalVolume::ReadDataFromBuf(unsigned long * BitOffset)
{
	unsigned long			errorcode;
	__int64					tempint64;
	
	GetBit(&errorcode,2);
	if ( errorcode == 0 )
	{
		GetBit64(&tempint64,10);
	}
	else if ( errorcode == 1 )
	{
		GetBit64(&tempint64,14);
	}
	else if ( errorcode == 2 )
	{
		GetBit64(&tempint64,18);
	}
	else
	{
		GetBit(&errorcode,2);
		if ( errorcode == 0 )
		{
			GetBit64(&tempint64,22);
		}
		else if ( errorcode == 1 )
		{
			GetBit64(&tempint64,26);
		}
		else if ( errorcode == 2 )
		{
			GetBit64(&tempint64,30);
		}
		else
		{
			GetBit64(&tempint64,40);
		}
	}
	
	SetData((double)tempint64);
}
//--------------------------------------------------------------------------------------------------------------------------
MFD_SubVolume::MFD_SubVolume(void)
{
	
}
//..........................................................................................................................
MFD_SubVolume::~MFD_SubVolume()
{
	
}
//..........................................................................................................................
void MFD_SubVolume::WriteDataToBuf(unsigned long * BitOffset)
{
	__int64					errorcode = (__int64)(GetData() + 0.5);

	assert(errorcode >= 0 && errorcode <= ((__int64)1 << 40));
	
	if ( errorcode < ((__int64)1 << 6) )
	{
		PutBit(0,2);
		PutBit64(errorcode,6);
	}
	else if ( errorcode < ((__int64)1 << 10) )
	{
		PutBit(1,2);
		PutBit64(errorcode,10);
	}
	else if ( errorcode < ((__int64)1 << 18) )
	{
		PutBit(2,2);
		PutBit64(errorcode,18);
	}
	else
	{
		PutBit(3,2);
		PutBit64(errorcode,40);
	}
}
//..........................................................................................................................
void MFD_SubVolume::ReadDataFromBuf(unsigned long * BitOffset)
{
	unsigned long			errorcode;
	__int64					tempint64;
	
	GetBit(&errorcode,2);
	if ( errorcode == 0 )
	{
		GetBit64(&tempint64,6);
	}
	else if ( errorcode == 1 )
	{
		GetBit64(&tempint64,10);
	}
	else if ( errorcode == 2 )
	{
		GetBit64(&tempint64,18);
	}
	else
	{
		GetBit64(&tempint64,40);
	}
	
	SetData((double)tempint64);
}
//--------------------------------------------------------------------------------------------------------------------------
MFD_SignSubVolume::MFD_SignSubVolume(void)
{
	
}
//..........................................................................................................................
MFD_SignSubVolume::~MFD_SignSubVolume()
{
	
}
//..........................................................................................................................
void MFD_SignSubVolume::WriteDataToBuf(unsigned long * BitOffset)
{
	__int64					errorcode = (__int64)(GetData() + 0.5);
	
	if ( errorcode > 0 )
	{
		PutBit(0,1);
	}
	else
	{
		PutBit(1,1);
		errorcode = -1 * errorcode;
	}

	assert(errorcode <= ((__int64)1 << 40));

	if ( errorcode < ((__int64)1 << 6) )
	{
		PutBit(0,2);
		PutBit64(errorcode,6);
	}
	else if ( errorcode < ((__int64)1 << 10) )
	{
		PutBit(1,2);
		PutBit64(errorcode,10);
	}
	else if ( errorcode < ((__int64)1 << 18) )
	{
		PutBit(2,2);
		PutBit64(errorcode,18);
	}
	else
	{
		PutBit(3,2);
		PutBit64(errorcode,40);
	}
}
//..........................................................................................................................
void MFD_SignSubVolume::ReadDataFromBuf(unsigned long * BitOffset)
{
	unsigned long			errorcode;
	__int64					tempint64;
	int						sign;

	GetBit(&errorcode,1);
	if ( errorcode == 0 )
	{
		sign = 1;
	}
	else
	{
		sign = -1;
	}
	
	GetBit(&errorcode,2);
	if ( errorcode == 0 )
	{
		GetBit64(&tempint64,6);
	}
	else if ( errorcode == 1 )
	{
		GetBit64(&tempint64,10);
	}
	else if ( errorcode == 2 )
	{
		GetBit64(&tempint64,18);
	}
	else
	{
		GetBit64(&tempint64,40);
	}
	
	SetData((double)tempint64 * sign);
}
//--------------------------------------------------------------------------------------------------------------------------
MFD_Amount::MFD_Amount(void)
{
	
}
//..........................................................................................................................
MFD_Amount::~MFD_Amount()
{
	
}
//..........................................................................................................................
void MFD_Amount::WriteDataToBuf(unsigned long * BitOffset)
{
	unsigned long				errorcode;
	float						tempfloat = GetData();

	assert(tempfloat >= 0);
	
	if ( tempfloat < (double)((unsigned long)1 << 7) )
	{
		errorcode = (unsigned long)tempfloat;
		
		PutBit(0,2);
		PutBit(errorcode,7);
	}
	else if ( (tempfloat / 100) < (double)((unsigned long)1 << 10) )
	{
		errorcode = (unsigned long)(tempfloat / 100);
		
		PutBit(1,2);
		PutBit(errorcode,10);
	}
	else if ( (tempfloat / 100) < (double)((unsigned long)1 << 17) )
	{
		errorcode = (unsigned long)(tempfloat / 100);
		
		PutBit(2,2);
		PutBit(errorcode,17);
	}
	else
	{
		memcpy(&errorcode,&tempfloat,4);
		
		PutBit(3,2);
		PutBit(errorcode,32);
	}
}
//..........................................................................................................................
void MFD_Amount::ReadDataFromBuf(unsigned long * BitOffset)
{
	unsigned long				errorcode;
	float						tempfloat;
	
	GetBit(&errorcode,2);
	if ( errorcode == 0 )
	{
		GetBit(&errorcode,7);
		tempfloat = (float)errorcode;
	}
	else if ( errorcode == 1 )
	{
		GetBit(&errorcode,10);
		tempfloat = (float)errorcode * 100;
	}
	else if ( errorcode ==2 )
	{
		GetBit(&errorcode,17);
		tempfloat = (float)errorcode * 100;
	}
	else
	{
		GetBit(&errorcode,32);
		memcpy(&tempfloat,&errorcode,4);
	}
	
	SetData(tempfloat);
}
//--------------------------------------------------------------------------------------------------------------------------
MFD_Records::MFD_Records(void)
{
	
}
//..........................................................................................................................
MFD_Records::~MFD_Records()
{
	
}
//..........................................................................................................................
void MFD_Records::WriteDataToBuf(unsigned long * BitOffset)
{
	unsigned long				errorcode = GetData();

	if ( errorcode < (double)((unsigned long)1 << 2) )
	{
		PutBit(0,2);
		PutBit(errorcode,2);
	}
	else if ( errorcode < (double)((unsigned long)1 << 5) )
	{
		PutBit(1,2);
		PutBit(errorcode,5);
	}
	else if ( errorcode < (double)((unsigned long)1 << 10) )
	{
		PutBit(2,2);
		PutBit(errorcode,10);
	}
	else
	{
		PutBit(3,2);
		PutBit(errorcode,32);
	}
}
//..........................................................................................................................
void MFD_Records::ReadDataFromBuf(unsigned long * BitOffset)
{
	unsigned long					errorcode;
	
	GetBit(&errorcode,2);
	if ( errorcode == 0 )
	{
		GetBit(&errorcode,2);
	}
	else if ( errorcode == 1 )
	{
		GetBit(&errorcode,5);
	}
	else if ( errorcode == 2 )
	{
		GetBit(&errorcode,10);
	}
	else
	{
		GetBit(&errorcode,32);
	}
	
	SetData(errorcode);
}
//--------------------------------------------------------------------------------------------------------------------------
MFD_PriceRate::MFD_PriceRate(void)
{
	
}
//..........................................................................................................................
MFD_PriceRate::~MFD_PriceRate()
{
	
}
//..........................................................................................................................
void MFD_PriceRate::WriteDataToBuf(unsigned long * BitOffset)
{
	unsigned long				errorcode = GetData();

	assert(errorcode <= ((unsigned long)1 << 16));
	
	if ( errorcode == 100 )
	{
		PutBit(0,1);
		PutBit(0,1);
	}
	else if ( errorcode == 1000 )
	{
		PutBit(0,1);
		PutBit(1,1);
	}
	else if ( errorcode < (double)((unsigned long)1 << 10) )
	{
		PutBit(2,2);
		PutBit(errorcode,10);
	}
	else
	{
		PutBit(3,2);
		PutBit(errorcode,16);
	}
}
//..........................................................................................................................
void MFD_PriceRate::ReadDataFromBuf(unsigned long * BitOffset)
{
	unsigned long					errorcode;
	
	GetBit(&errorcode,1);
	if ( errorcode == 0 )
	{
		GetBit(&errorcode,1);
		if ( errorcode == 0 )
		{
			errorcode = 100;
		}
		else
		{
			errorcode = 1000;
		}
	}
	else
	{
		GetBit(&errorcode,1);
		if ( errorcode == 0 )
		{
			GetBit(&errorcode,10);
		}
		else
		{
			GetBit(&errorcode,16);
		}
	}
	
	SetData((unsigned short)errorcode);
}
//--------------------------------------------------------------------------------------------------------------------------
MFD_SubULong::MFD_SubULong(void)
{

}
//..........................................................................................................................
MFD_SubULong::~MFD_SubULong()
{

}
//..........................................................................................................................
void MFD_SubULong::WriteDataToBuf(unsigned long * BitOffset)
{
	unsigned long				errorcode = GetData();

	if ( errorcode < ((unsigned long)1 << 1) )
	{
		PutBit(0,1);
		PutBit(errorcode,1);
	}
	else if ( errorcode < ((unsigned long)1 << 3) )
	{
		PutBit(2,2);
		PutBit(errorcode,3);
	}
	else if ( errorcode < ((unsigned long)1 << 8) )
	{
		PutBit(6,3);
		PutBit(errorcode,8);
	}
	else if ( errorcode < ((unsigned long)1 << 16) )
	{
		PutBit(14,4);
		PutBit(errorcode,16);
	}
	else
	{
		PutBit(15,4);
		PutBit(errorcode,32);
	}
}
//..........................................................................................................................
void MFD_SubULong::ReadDataFromBuf(unsigned long * BitOffset)
{
	unsigned long					errorcode;

	GetBit(&errorcode,1);
	if ( errorcode == 0 )
	{
		GetBit(&errorcode,1);
	}
	else
	{
		GetBit(&errorcode,1);
		if ( errorcode == 0 )
		{
			GetBit(&errorcode,3);
		}
		else
		{
			GetBit(&errorcode,1);
			if ( errorcode == 0 )
			{
				GetBit(&errorcode,8);
			}
			else
			{
				GetBit(&errorcode,1);
				if ( errorcode == 0 )
				{
					GetBit(&errorcode,16);
				}
				else
				{		
					GetBit(&errorcode,32);
				}
			}
		}
	}

	SetData(errorcode);
}
//--------------------------------------------------------------------------------------------------------------------------
MFD_Bool::MFD_Bool(void)
{
	
}
//..........................................................................................................................
MFD_Bool::~MFD_Bool()
{
	
}
//..........................................................................................................................
void MFD_Bool::WriteDataToBuf(unsigned long * BitOffset)
{
	unsigned long				errorcode = GetData();

	assert(errorcode <= 1);
	
	PutBit(errorcode,1);
}
//..........................................................................................................................
void MFD_Bool::ReadDataFromBuf(unsigned long * BitOffset)
{
	unsigned long					errorcode;
	
	GetBit(&errorcode,1);
	
	SetData((unsigned char)errorcode);
}
//--------------------------------------------------------------------------------------------------------------------------
MFD_Date::MFD_Date(void)
{
	
}
//..........................................................................................................................
MFD_Date::~MFD_Date()
{
	
}
//..........................................................................................................................
void MFD_Date::WriteDataToBuf(unsigned long * BitOffset)
{
	unsigned long				errorcode = GetData();
	unsigned long				templong;
	long						year,mon,day;
	
	if ( errorcode == 0 )
	{
		//处理特殊的日期为空的值
		PutBit(0,2);
		return;
	}

	year = (errorcode / 10000);
	mon = (errorcode % 10000) / 100;
	day = (errorcode % 100);

	assert(year > 0);
	assert(mon >= 1 && mon <= 12);
	assert(day >= 1 && day <= 31);
	
	if ( errorcode >= 20000000 )
	{
		PutBit(1,2);
		templong = (year - 2000) * 372 + ((mon - 1) * 31) + (day - 1);
	}
	else
	{
		PutBit(2,2);
		templong = (2000 - year) * 372 + ((mon - 1) * 31) + (day - 1);
	}
	
	if ( templong < ((unsigned long)1 << 12) )
	{
		PutBit(0,2);
		PutBit(templong,12);
	}
	else if ( templong < ((unsigned long)1 << 16) )
	{
		PutBit(1,2);
		PutBit(templong,16);
	}
	else if ( templong < ((unsigned long)1 << 20) )
	{
		PutBit(2,2);
		PutBit(templong,20);
	}
	else
	{
		PutBit(3,2);
		PutBit(templong,32);
	}
}
//..........................................................................................................................
void MFD_Date::ReadDataFromBuf(unsigned long * BitOffset)
{
	register int				sign;
	unsigned long				errorcode;
	long						year,mon,day;
	
	GetBit(&errorcode,2);
	if ( errorcode == 0 )
	{
		//处理特殊的空值
		SetData(0);
		return;
	}
	else if ( errorcode == 1 )
	{
		sign = 1;
	}
	else
	{
		sign = -1;
	}
	
	GetBit(&errorcode,2);
	if ( errorcode == 0 )
	{
		GetBit(&errorcode,12);
	}
	else if ( errorcode == 1 )
	{
		GetBit(&errorcode,16);
	}
	else if ( errorcode == 2 )
	{
		GetBit(&errorcode,20);
	}
	else
	{
		GetBit(&errorcode,32);
	}
	
	year = errorcode / 372;
	mon = (errorcode % 372) / 31 + 1;
	day = errorcode % 31 + 1;
	
	if ( sign > 0 )
	{
		SetData( (2000+year) * 10000 + (mon * 100) + day );
	}
	else
	{
		SetData( (2000-year) * 10000 + (mon * 100) + day );
	}
}
//--------------------------------------------------------------------------------------------------------------------------
MFD_Time::MFD_Time(void)
{
	
}
//..........................................................................................................................
MFD_Time::~MFD_Time()
{
	
}
//..........................................................................................................................
void MFD_Time::WriteDataToBuf(unsigned long * BitOffset)
{
	unsigned long				errorcode = GetData();
	unsigned long				templong;
	long						hour,min,sec;
	
	hour = errorcode / 10000;
	min = (errorcode % 10000) / 100;
	sec = errorcode % 100;

	assert(hour >= 0 && hour < 24);
	assert(min >= 0 && min < 60);
	assert(sec >= 0 && sec < 60);
	
	if ( errorcode >= 120000 )
	{
		PutBit(0,1);
		templong = (hour - 12) * 3600 + (min * 60) + sec;
	}
	else
	{
		PutBit(1,1);
		templong = (12 - hour) * 3600 + (min * 60) + sec;
	}
	
	if ( templong < ((unsigned long)1 << 14) )
	{
		PutBit(0,1);
		PutBit(templong,14);
	}
	else
	{
		PutBit(1,1);
		PutBit(templong,16);
	}
}
//..........................................................................................................................
void MFD_Time::ReadDataFromBuf(unsigned long * BitOffset)
{
	register int				sign;
	unsigned long				errorcode;
	long						hour,min,sec;
	
	GetBit(&errorcode,1);
	if ( errorcode == 0 )
	{
		sign = 1;
	}
	else
	{
		sign = -1;
	}
	
	GetBit(&errorcode,1);
	if ( errorcode == 0 )
	{
		GetBit(&errorcode,14);
	}
	else
	{
		GetBit(&errorcode,16);
	}
	
	hour = errorcode / 3600;
	min = (errorcode % 3600) / 60;
	sec = errorcode % 60;
	
	if ( sign > 0 )
	{
		SetData((hour + 12) * 10000 + (min * 100) + sec);
	}
	else
	{
		SetData((12 - hour) * 10000 + (min * 100) + sec);
	}
}
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
MFinanceData::MFinanceData(void)
{
	m_RecordData = NULL;
	m_MaxRecord = 0;
	m_CurBitSize = 0;
	m_RemainBitSize = 0;
	
	m_IsFinanceDataFlag = true;
	m_DefaultSize = 0;
}
//..........................................................................................................................
MFinanceData::~MFinanceData()
{
	m_RecordData = NULL;
	m_MaxRecord = 0;
	m_CurBitSize = 0;
	m_RemainBitSize = 0;
}
//..........................................................................................................................
void MFinanceData::AttchBufToRead(char * InBuf,unsigned long InSize)
{
	m_RecordData = InBuf;
	m_MaxRecord = InSize;
	m_RemainBitSize = (unsigned char)InBuf[0];

	if ( m_RemainBitSize == 0xFF )
	{
		m_IsFinanceDataFlag = false;
		m_CurBitSize = 1;
		m_RemainBitSize = 0;
	}
	else
	{
		m_IsFinanceDataFlag = true;
		m_CurBitSize = 8;
	}
}
//..........................................................................................................................
void MFinanceData::AttchBufToWrite(char * InBuf,unsigned long InSize)
{
	memset(InBuf,0x00,InSize);

	m_RecordData = InBuf;
	m_MaxRecord = InSize;
	m_CurBitSize = 8;
	m_RemainBitSize = 0;

	m_IsFinanceDataFlag = true;
	m_DefaultSize = 1;
}
//..........................................................................................................................
int  MFinanceData::ReadData(char * OutBuf,unsigned long InSize)
{
	register int				errorcode,i;
	MFinanceBaseData		*	dataptr;

	if ( m_IsFinanceDataFlag == true )
	{
		try
		{
			errorcode = InSize / sizeof(MFinanceBaseData);
			for ( i=0;i<errorcode;i++ )
			{
				dataptr = (MFinanceBaseData *)(OutBuf + sizeof(MFinanceBaseData) * i);

				dataptr->AttchBuf(m_RecordData,m_MaxRecord * 8 - m_RemainBitSize);
				dataptr->ReadDataFromBuf(&m_CurBitSize);
			}

			return(m_CurBitSize);
		}
		catch(int  e)
		{
			return(e);
		}
	}
	else
	{
		try
		{
			errorcode = InSize / sizeof(MFinanceBaseData);
			for ( i=0;i<errorcode;i++ )
			{
				dataptr = (MFinanceBaseData *)(OutBuf + sizeof(MFinanceBaseData) * i);
				
				dataptr->AttchBuf(m_RecordData,m_MaxRecord * 8 - m_RemainBitSize);
				if ( dataptr->ReadDefaultData(&m_CurBitSize) < 0 )
				{
					return(MFINANCEDATA_ERR_EMPTY);
				}
			}
			
			return(m_CurBitSize);
		}
		catch(int  e)
		{
			return(e);
		}
	}
}
//..........................................................................................................................
int  MFinanceData::WriteData(char * InBuf,unsigned long InSize)
{
	register int				errorcode,i;
	MFinanceBaseData		*	dataptr;

	try
	{
		errorcode = InSize / sizeof(MFinanceBaseData);
		for ( i=0;i<errorcode;i++ )
		{
			dataptr = (MFinanceBaseData *)(InBuf + sizeof(MFinanceBaseData) * i);

			if ( dataptr->WriteDefaultData(m_DefaultData,&m_DefaultSize) < 0 )
			{
				return(MFINANCEDATA_ERR_FULL);
			}

			if ( m_IsFinanceDataFlag == true )
			{				
				dataptr->AttchBuf(m_RecordData,m_MaxRecord * 8 - m_RemainBitSize);
				dataptr->WriteDataToBuf(&m_CurBitSize);
			}
		}
		
		return(m_CurBitSize);
	}
	catch(int  e)
	{
		if ( e == MFINANCEDATA_ERR_FULL )
		{
			m_IsFinanceDataFlag = false;
		}
		else
		{
			return(e);
		}
	}

	return((int)m_DefaultSize * 8);
}
//..........................................................................................................................
int  MFinanceData::GetCurSize(void)
{
	if ( m_IsFinanceDataFlag == true )
	{
		if ( m_CurBitSize % 8 == 0 )
		{
			if ( m_MaxRecord > 0 )
			{
				m_RemainBitSize = 0;
				m_RecordData[0] = m_RemainBitSize;
			}

			return(m_CurBitSize / 8);
		}
		else
		{
			if ( m_MaxRecord > 0 )
			{
				m_RemainBitSize = (unsigned char)(8 - (m_CurBitSize % 8));
				m_RecordData[0] = m_RemainBitSize;
			}

			return(m_CurBitSize / 8 + 1);
		}
	}
	else
	{
		assert(m_RecordData != NULL);
		assert(m_DefaultSize <= m_MaxRecord);

		m_DefaultData[0] = -1;
		memcpy(m_RecordData,m_DefaultData,m_DefaultSize);

		return(m_DefaultSize);
	}
}
//--------------------------------------------------------------------------------------------------------------------------
