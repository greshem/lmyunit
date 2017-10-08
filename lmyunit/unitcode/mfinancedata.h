//--------------------------------------------------------------------------------------------------------------------------
//                  ;;;,
//        ,;;;;;: ,;;;:.,;..
//         :;;"`,;;;;;;"":;;					单元名称：金融数据单元
//      ..;;:  .;;,.;;:',;;"					备注信息：
//    ,;;;;;;" :;`',;",;;"						
//   :" ,;:` , `:.;;;;;'
//    ,;;;,;:;;,;;;, ,;							
//   :;;;"` `:;;;;;,;,.;.
//   '""   .;;`.;";:;;;;` ;,					
//       .;"`  ::. '   .,;;;
//      ""     ';;;;;;;;;;`
//--------------------------------------------------------------------------------------------------------------------------
#ifndef __MEngine_MFinanceDataH__
#define __MEngine_MFinanceDataH__
//--------------------------------------------------------------------------------------------------------------------------
#include "stdio.h"
#include "memory.h"
#include "assert.h"
#ifndef WINDOWSCODE
	#include "mstring.h"
#endif
//--------------------------------------------------------------------------------------------------------------------------
#define				MFINANCEDATA_ERR_FULL				-1
#define				MFINANCEDATA_ERR_EMPTY				-2
#define				MFINANCEDATA_ERR_NOMEMORY			-3
//--------------------------------------------------------------------------------------------------------------------------
#define				MFINANCEDATA_MAX_SIZE				8192
//--------------------------------------------------------------------------------------------------------------------------
class MFinanceBaseData
{
protected:
	char				*	m_RecordData;
	unsigned long			m_MaxBitSize;
protected:
	char				*	m_Value;
	char					m_DefaultBuf[16];
	unsigned long			m_MaxValueSize;
protected:
	//..........................................................................................................................
	__inline void inner_putbit(unsigned long * BitOffset,unsigned long Value,unsigned long BitSize)
	{
		register unsigned long								byteoffset;
		register unsigned long								bytestart;
		
		if ( (* BitOffset) >= m_MaxBitSize )
		{
			throw MFINANCEDATA_ERR_FULL;
			return;
		}
		
		byteoffset = (* BitOffset) >> 3;
		bytestart = (* BitOffset) - ( ((* BitOffset) >> 3) << 3 );
		
		if ( ( 8 - bytestart ) >= BitSize )
		{
			m_RecordData[byteoffset] = (unsigned char)(m_RecordData[byteoffset] | ( Value << ( 8 - bytestart - BitSize ) ));
			(* BitOffset) += BitSize;
		}
		else
		{
			m_RecordData[byteoffset] = (unsigned char)(m_RecordData[byteoffset] | ( Value >> ( BitSize - 8 + bytestart ) ));
			
			(* BitOffset) += 8 - bytestart;
			BitSize -= (unsigned short)(8 - bytestart);
			Value = Value & ( 0xFFFFFFFF >> (32 - BitSize) );
			
			inner_putbit(BitOffset,Value,BitSize);
		}
	}
	//..........................................................................................................................
	__inline void inner_putbit64(unsigned long * BitOffset,__int64 Value,unsigned long BitSize)
	{
		unsigned long					high,low;
		
		memcpy(&high,((char *)&Value) + 4,4);
		memcpy(&low,(char *)&Value,4);
		
		if ( BitSize > 32 )
		{
			inner_putbit(BitOffset,low,32);
			inner_putbit(BitOffset,high,BitSize - 32);
		}
		else
		{
			inner_putbit(BitOffset,low,BitSize);
		}
	}
	//..........................................................................................................................
	__inline void inner_putbitstring(unsigned long * BitOffset,char * Value,unsigned long BitSize)
	{
		register int					i = 0;
		
		while ( BitSize > 0 )
		{
			if ( BitSize > 8 )
			{
				inner_putbit(BitOffset,(unsigned long)((unsigned char)Value[i]),8);
				
				i ++;
				BitSize -= 8;
			}
			else
			{
				inner_putbit(BitOffset,(unsigned long)((unsigned char)Value[i]),BitSize);
				return;
			}
		}
	}
protected:
	//..........................................................................................................................
	__inline void inner_getbit(unsigned long * BitOffset,unsigned long * Value,unsigned long BitSize)
	{
		register unsigned long									byteoffset;
		register unsigned long									bytestart;
		register unsigned char									invalue;
		register unsigned long									tempvalue;
		
		if ( (* BitOffset) >= m_MaxBitSize )
		{
			//超过最大长度，抛出异常
			throw MFINANCEDATA_ERR_EMPTY;
			return;
		}
		
		* Value = 0;
		byteoffset = (* BitOffset) >> 3;
		bytestart = (* BitOffset) - ( ((* BitOffset) >> 3) << 3 );
		
		if ( ( 8 - bytestart ) >= BitSize )
		{
			invalue = m_RecordData[byteoffset];
			* Value = (unsigned long)((invalue & ( 0xFF >> bytestart )) >> ( 8 - bytestart - BitSize ));
			(* BitOffset) += BitSize;
		}
		else
		{
			invalue = m_RecordData[byteoffset];
			* Value = (invalue & ( 0xFF >> bytestart ));
			
			(* BitOffset) += 8 - bytestart;
			BitSize -= (unsigned short)(8 - bytestart);
			
			inner_getbit(BitOffset,&tempvalue,BitSize);
			
			* Value = (( * Value ) << BitSize) | tempvalue;
		}
	}
	//..........................................................................................................................
	__inline void inner_getbit64(unsigned long * BitOffset,__int64 * Value,unsigned long BitSize)
	{
		unsigned long					high = 0,low = 0;
		
		if ( BitSize > 32 )
		{
			inner_getbit(BitOffset,&low,32);
			inner_getbit(BitOffset,&high,BitSize - 32);
		}
		else
		{
			inner_getbit(BitOffset,&low,BitSize);
		}
		
		memcpy(((char *)Value) + 4,&high,4);
		memcpy((char *)Value,&low,4);
	}
	//..........................................................................................................................
	__inline void inner_getbitstring(unsigned long * BitOffset,char * Value,unsigned long BitSize)
	{
		register int				i = 0;
		unsigned long				errorcode;
		
		while ( BitSize > 0 )
		{
			if ( BitSize > 8 )
			{
				inner_getbit(BitOffset,&errorcode,8);
				
				Value[i] = (unsigned char)errorcode;
				i ++;
				BitSize -= 8;
			}
			else
			{
				inner_getbit(BitOffset,&errorcode,BitSize);
				Value[i] = (unsigned char)errorcode;
				
				return;
			}
		}
	}
protected:
	__inline void inner_realloc(unsigned long InSize)
	{
		char				*	tempptr = NULL;
		
		if ( InSize <= m_MaxValueSize )
		{
			return;
		}
		
		tempptr = new char[InSize];
		if ( tempptr == NULL )
		{
			throw MFINANCEDATA_ERR_NOMEMORY;
			return;
		}
		
		memcpy(tempptr,m_Value,m_MaxValueSize);
		
		if ( m_Value != m_DefaultBuf )
			delete[] m_Value;
		
		m_Value = tempptr;
		m_MaxValueSize = InSize;
	}
public:
	MFinanceBaseData(void);
	virtual ~MFinanceBaseData();
public:
	void AttchBuf(char * InBuf,unsigned long InSize);
public:
	virtual void WriteDataToBuf(unsigned long * BitOffset);
	virtual void ReadDataFromBuf(unsigned long * BitOffset);
	virtual int  ReadDefaultData(unsigned long * Offset);
	virtual int  WriteDefaultData(char * InBuf,unsigned long * Offset);
};
//--------------------------------------------------------------------------------------------------------------------------
//标准的数据类型莫版
template<class templateRecord> class MFinanceNumBaseData : public MFinanceBaseData
{
public:
	MFinanceNumBaseData(void);
	virtual ~MFinanceNumBaseData();
public:
	virtual void operator = (templateRecord In);
	virtual templateRecord GetData(void);
	virtual int  ReadDefaultData(unsigned long * Offset);
	virtual int  WriteDefaultData(char * InBuf,unsigned long * Offset);
public:
	void SetData(templateRecord In);
};
//..........................................................................................................................
//莫版类实现部分
template<class templateRecord> MFinanceNumBaseData<templateRecord>::MFinanceNumBaseData(void)
{

}
//..........................................................................................................................
template<class templateRecord> MFinanceNumBaseData<templateRecord>::~MFinanceNumBaseData(void)
{
	
}
//..........................................................................................................................
template<class templateRecord> void MFinanceNumBaseData<templateRecord>::operator = (templateRecord In)
{
	memcpy(m_Value,(char *)&In,sizeof(templateRecord));
}
//..........................................................................................................................
template<class templateRecord> void MFinanceNumBaseData<templateRecord>::SetData (templateRecord In)
{
	memcpy(m_Value,(char *)&In,sizeof(templateRecord));
}
//..........................................................................................................................
template<class templateRecord> templateRecord MFinanceNumBaseData<templateRecord>::GetData(void)
{
	templateRecord				errorcode;

	memcpy((char *)&errorcode,m_Value,sizeof(templateRecord));

	return(errorcode);
}
//..........................................................................................................................
template<class templateRecord> int  MFinanceNumBaseData<templateRecord>::ReadDefaultData(unsigned long * Offset)
{
	if ( ((* Offset) + sizeof(templateRecord)) > (m_MaxBitSize / 8) )
	{
		return(-1);
	}

	memcpy(m_Value,m_RecordData + (* Offset),sizeof(templateRecord));
	(* Offset) += sizeof(templateRecord);

	return(1);
}
//..........................................................................................................................
template<class templateRecord> int  MFinanceNumBaseData<templateRecord>::WriteDefaultData(char * InBuf,unsigned long * Offset)
{
	if ( ((* Offset) + sizeof(templateRecord)) >= MFINANCEDATA_MAX_SIZE )
	{
		return(-1);
	}

	memcpy(InBuf + (* Offset),m_Value,sizeof(templateRecord));
	(* Offset) += sizeof(templateRecord);

	return(1);
}
//--------------------------------------------------------------------------------------------------------------------------
//标准C++类型莫版
template<class templateRecord> class MFD_CStandType : public MFinanceBaseData
{
public:
	MFD_CStandType(void);
	virtual ~MFD_CStandType();
public:
	virtual void operator = (templateRecord In);
	virtual templateRecord GetData(void);
public:
	virtual void WriteDataToBuf(unsigned long * BitOffset);
	virtual void ReadDataFromBuf(unsigned long * BitOffset);
	virtual int  ReadDefaultData(unsigned long * Offset);
	virtual int  WriteDefaultData(char * InBuf,unsigned long * Offset);
};
//..........................................................................................................................
//莫版类实现部分
template<class templateRecord> MFD_CStandType<templateRecord>::MFD_CStandType(void)
{
	
}
//..........................................................................................................................
template<class templateRecord> MFD_CStandType<templateRecord>::~MFD_CStandType(void)
{
	
}
//..........................................................................................................................
template<class templateRecord> void MFD_CStandType<templateRecord>::operator = (templateRecord In)
{
	memcpy(m_Value,(char *)&In,sizeof(templateRecord));
}
//..........................................................................................................................
template<class templateRecord> templateRecord MFD_CStandType<templateRecord>::GetData(void)
{
	templateRecord				errorcode;
	
	memcpy((char *)&errorcode,m_Value,sizeof(templateRecord));
	
	return(errorcode);
}
//..........................................................................................................................
template<class templateRecord> void MFD_CStandType<templateRecord>::WriteDataToBuf(unsigned long * BitOffset)
{
	inner_putbitstring(BitOffset,m_Value,sizeof(templateRecord) * 8);
}
//..........................................................................................................................
template<class templateRecord> void MFD_CStandType<templateRecord>::ReadDataFromBuf(unsigned long * BitOffset)
{
	inner_getbitstring(BitOffset,m_Value,sizeof(templateRecord) * 8);
}
//..........................................................................................................................
template<class templateRecord> int  MFD_CStandType<templateRecord>::ReadDefaultData(unsigned long * Offset)
{
	if ( ((* Offset) + sizeof(templateRecord)) > (m_MaxBitSize / 8) )
	{
		return(-1);
	}

	memcpy(m_Value,m_RecordData + (* Offset),sizeof(templateRecord));
	(* Offset) += sizeof(templateRecord);

	return(1);
}
//..........................................................................................................................
template<class templateRecord> int  MFD_CStandType<templateRecord>::WriteDefaultData(char * InBuf,unsigned long * Offset)
{
	if ( ((* Offset) + sizeof(templateRecord)) >= MFINANCEDATA_MAX_SIZE )
	{
		return(-1);
	}

	memcpy(InBuf + (* Offset),m_Value,sizeof(templateRecord));
	(* Offset) += sizeof(templateRecord);

	return(1);
}
//--------------------------------------------------------------------------------------------------------------------------
//定义C++的标准类型
typedef MFD_CStandType<char>					MFD_Char;
typedef MFD_CStandType<unsigned char>			MFD_UChar;
typedef MFD_CStandType<short>					MFD_Short;
typedef MFD_CStandType<unsigned short>			MFD_UShort;
typedef MFD_CStandType<long>					MFD_Long;
typedef MFD_CStandType<unsigned long>			MFD_ULong;
typedef MFD_CStandType<float>					MFD_Float;
typedef MFD_CStandType<double>					MFD_Double;
//--------------------------------------------------------------------------------------------------------------------------
//类型名称：市场编号
//表示范围：0--255
//匹配类型：unsined char
class MFD_MarketID : public MFinanceNumBaseData<unsigned char>
{
public:
	MFD_MarketID(void);
	virtual ~MFD_MarketID();
public:
	virtual void WriteDataToBuf(unsigned long * BitOffset);
	virtual void ReadDataFromBuf(unsigned long * BitOffset);
public:
	virtual void operator = (unsigned char In)
	{
		SetData(In);
	}
};
//--------------------------------------------------------------------------------------------------------------------------
//类型名称：市场状态
//表示范围：0--255
//匹配类型：unsined char
typedef MFD_MarketID							MFD_MarketStatus;
//--------------------------------------------------------------------------------------------------------------------------
//类型名称：商品类别
//表示范围：0--255
//匹配类型：unsined char
class MFD_WareType : public MFinanceNumBaseData<unsigned char>
{
public:
	MFD_WareType(void);
	virtual ~MFD_WareType();
public:
	virtual void WriteDataToBuf(unsigned long * BitOffset);
	virtual void ReadDataFromBuf(unsigned long * BitOffset);
public:
	virtual void operator = (unsigned char In)
	{
		SetData(In);
	}
};
//--------------------------------------------------------------------------------------------------------------------------
//类型名称：时区
//表示范围：-12 -- +12
//匹配类型：char
class MFD_TimeZoom : public MFinanceNumBaseData<char>
{
public:
	MFD_TimeZoom(void);
	virtual ~MFD_TimeZoom();
public:
	virtual void WriteDataToBuf(unsigned long * BitOffset);
	virtual void ReadDataFromBuf(unsigned long * BitOffset);
public:
	virtual void operator = (char In)
	{
		SetData(In);
	}
};
//--------------------------------------------------------------------------------------------------------------------------
//类型名称：商品序号
//表示范围：0--2的16次方
//匹配类型：unsigned short
class MFD_WareSerial : public MFinanceNumBaseData<unsigned short>
{
public:
	MFD_WareSerial(void);
	virtual ~MFD_WareSerial();
public:
	virtual void WriteDataToBuf(unsigned long * BitOffset);
	virtual void ReadDataFromBuf(unsigned long * BitOffset);
public:
	virtual void operator = (unsigned short In)
	{
		SetData(In);
	}
};
//--------------------------------------------------------------------------------------------------------------------------
//类型名称：商品价格 * 放大倍数[注意：放大倍数根据市场种类来决定]
//表示范围：0 -- 2的32次方
//匹配类型：unsigned long
class MFD_Price : public MFinanceNumBaseData<unsigned long>
{
public:
	MFD_Price(void);
	virtual ~MFD_Price();
public:
	virtual void WriteDataToBuf(unsigned long * BitOffset);
	virtual void ReadDataFromBuf(unsigned long * BitOffset);
public:
	virtual void operator = (unsigned long In)
	{
		SetData(In);
	}
};
//--------------------------------------------------------------------------------------------------------------------------
//类型名称：商品无符号差价 * 放大倍数[注意：放大倍数根据市场种类来决定]
//表示范围：0 -- 2的32次方
//匹配类型：unsigned long
class MFD_SubPrice : public MFinanceNumBaseData<unsigned long>
{
public:
	MFD_SubPrice(void);
	virtual ~MFD_SubPrice();
public:
	virtual void WriteDataToBuf(unsigned long * BitOffset);
	virtual void ReadDataFromBuf(unsigned long * BitOffset);
public:
	virtual void operator = (unsigned long In)
	{
		SetData(In);
	}
};
//--------------------------------------------------------------------------------------------------------------------------
//类型名称：商品有符号差价 * 放大倍数[注意：放大倍数根据市场种类来决定]
//表示范围：-(2的31次方) --- 2的31次方 - 1
//匹配类型：long
class MFD_SignSubPrice : public MFinanceNumBaseData<long>
{
public:
	MFD_SignSubPrice(void);
	virtual ~MFD_SignSubPrice();
public:
	virtual void WriteDataToBuf(unsigned long * BitOffset);
	virtual void ReadDataFromBuf(unsigned long * BitOffset);
public:
	virtual void operator = (long In)
	{
		SetData(In);
	}
};
//--------------------------------------------------------------------------------------------------------------------------
//类型名称：总成交量
//表示范围：0 -- 2的40次方
//匹配类型：double
class MFD_TotalVolume : public MFinanceNumBaseData<double>
{
public:
	MFD_TotalVolume(void);
	virtual ~MFD_TotalVolume();
public:
	virtual void WriteDataToBuf(unsigned long * BitOffset);
	virtual void ReadDataFromBuf(unsigned long * BitOffset);
public:
	virtual void operator = (double In)
	{
		SetData(In);
	}
};
//--------------------------------------------------------------------------------------------------------------------------
//类型名称：现量[成交量之差]
//表示范围：0 -- 2的40次方
//匹配类型：double
class MFD_SubVolume : public MFinanceNumBaseData<double>
{
public:
	MFD_SubVolume(void);
	virtual ~MFD_SubVolume();
public:
	virtual void WriteDataToBuf(unsigned long * BitOffset);
	virtual void ReadDataFromBuf(unsigned long * BitOffset);
public:
	virtual void operator = (double In)
	{
		SetData(In);
	}
};
//--------------------------------------------------------------------------------------------------------------------------
//类型名称：有符号的现量[成交量之差，可能有符号，如期货中的仓差]
//表示范围：0 -- 2的40次方
//匹配类型：double
class MFD_SignSubVolume : public MFinanceNumBaseData<double>
{
public:
	MFD_SignSubVolume(void);
	virtual ~MFD_SignSubVolume();
public:
	virtual void WriteDataToBuf(unsigned long * BitOffset);
	virtual void ReadDataFromBuf(unsigned long * BitOffset);
public:
	virtual void operator = (double In)
	{
		SetData(In);
	}
};
//--------------------------------------------------------------------------------------------------------------------------
//类型名称：成交金额
//表示范围：类似于C++的float，没有范围，但会损失精度
//匹配类型：float
class MFD_Amount : public MFinanceNumBaseData<float>
{
public:
	MFD_Amount(void);
	virtual ~MFD_Amount();
public:
	virtual void WriteDataToBuf(unsigned long * BitOffset);
	virtual void ReadDataFromBuf(unsigned long * BitOffset);
public:
	virtual void operator = (float In)
	{
		SetData(In);
	}
};
//--------------------------------------------------------------------------------------------------------------------------
//类型名称：成交金额
//表示范围：类似于C++的double，0 -- 2的40次方，但会损失精度
//匹配类型：double
typedef MFD_TotalVolume MFD_HighAmount;
//--------------------------------------------------------------------------------------------------------------------------
//类型名称：成交比数
//表示范围：0--2的32次方
//匹配类型：unsigned long
class MFD_Records : public MFinanceNumBaseData<unsigned long>
{
public:
	MFD_Records(void);
	virtual ~MFD_Records();
public:
	virtual void WriteDataToBuf(unsigned long * BitOffset);
	virtual void ReadDataFromBuf(unsigned long * BitOffset);
public:
	virtual void operator = (unsigned long In)
	{
		SetData(In);
	}
};
//--------------------------------------------------------------------------------------------------------------------------
//类型名称：价格放大倍数
//表示范围：0--2的16次方
//匹配类型：unsigned short
class MFD_PriceRate : public MFinanceNumBaseData<unsigned short>
{
public:
	MFD_PriceRate(void);
	virtual ~MFD_PriceRate();
public:
	virtual void WriteDataToBuf(unsigned long * BitOffset);
	virtual void ReadDataFromBuf(unsigned long * BitOffset);
public:
	virtual void operator = (unsigned short In)
	{
		SetData(In);
	}
};
//--------------------------------------------------------------------------------------------------------------------------
//类型名称：标准日期YYYYMMDD格式
//表示范围：0--9999年12月31日
//匹配类型：unsigned long
class MFD_Date : public MFinanceNumBaseData<unsigned long>
{
public:
	MFD_Date(void);
	virtual ~MFD_Date();
public:
	virtual void WriteDataToBuf(unsigned long * BitOffset);
	virtual void ReadDataFromBuf(unsigned long * BitOffset);
public:
	virtual void operator = (unsigned long In)
	{
		SetData(In);
	}
};
//--------------------------------------------------------------------------------------------------------------------------
//类型名称：无符号整数差值
//表示范围：0--2的32次方
//匹配类型：unsigned long
class MFD_SubULong : public MFinanceNumBaseData<unsigned long>
{
public:
	MFD_SubULong(void);
	virtual ~MFD_SubULong();
public:
	virtual void WriteDataToBuf(unsigned long * BitOffset);
	virtual void ReadDataFromBuf(unsigned long * BitOffset);
public:
	virtual void operator = (unsigned long In)
	{
		SetData(In);
	}
};
//--------------------------------------------------------------------------------------------------------------------------
//类型名称：标准BOOL型
//表示范围：true和false
//匹配类型：unsigned char
class MFD_Bool : public MFinanceNumBaseData<unsigned char>
{
public:
	MFD_Bool(void);
	virtual ~MFD_Bool();
public:
	virtual void WriteDataToBuf(unsigned long * BitOffset);
	virtual void ReadDataFromBuf(unsigned long * BitOffset);
public:
	virtual void operator = (unsigned char In)
	{
		SetData(In);
	}
};
//--------------------------------------------------------------------------------------------------------------------------
//类型名称：标准时间HHMMSS格式
//表示范围：0--23:59:59
//匹配类型：unsigned long
class MFD_Time : public MFinanceNumBaseData<unsigned long>
{
public:
	MFD_Time(void);
	virtual ~MFD_Time();
public:
	virtual void WriteDataToBuf(unsigned long * BitOffset);
	virtual void ReadDataFromBuf(unsigned long * BitOffset);
public:
	virtual void operator = (unsigned long In)
	{
		SetData(In);
	}
};
//--------------------------------------------------------------------------------------------------------------------------
//类型名称：固定长度字符串（缓冲）等数据
//表示范围：没有范围
//匹配类型：char []
template<int stringsize> class MFD_String : public MFinanceBaseData
{
protected:
public:
	MFD_String(void);
	virtual ~MFD_String();
public:
	virtual void WriteDataToBuf(unsigned long * BitOffset);
	virtual void ReadDataFromBuf(unsigned long * BitOffset);
	virtual int  ReadDefaultData(unsigned long * Offset);
	virtual int  WriteDefaultData(char * InBuf,unsigned long * Offset);
public:
	virtual void operator = (char * In);
	void GetData(char * OutBuf);
};
//..........................................................................................................................
template<int stringsize> MFD_String<stringsize>::MFD_String(void)
{
	
}
//..........................................................................................................................
template<int stringsize> MFD_String<stringsize>::~MFD_String(void)
{
	
}
//..........................................................................................................................
template<int stringsize> void MFD_String<stringsize>::operator = (char * InBuf)
{
	inner_realloc(stringsize);
	
	memcpy(m_Value,InBuf,stringsize);
}
//..........................................................................................................................
template<int stringsize> void MFD_String<stringsize>::GetData(char * OutBuf)
{
	memcpy(OutBuf,m_Value,stringsize);
}
//..........................................................................................................................
template<int stringsize> void MFD_String<stringsize>::WriteDataToBuf(unsigned long * BitOffset)
{
	inner_putbitstring(BitOffset,m_Value,stringsize * 8);
}
//..........................................................................................................................
template<int stringsize> void MFD_String<stringsize>::ReadDataFromBuf(unsigned long * BitOffset)
{
	inner_getbitstring(BitOffset,m_Value,stringsize * 8);
}
//..........................................................................................................................
template<int stringsize> int  MFD_String<stringsize>::ReadDefaultData(unsigned long * Offset)
{
	if ( ((* Offset) + stringsize) > (m_MaxBitSize / 8) )
	{
		return(-1);
	}

	memcpy(m_Value,m_RecordData + (* Offset),stringsize);
	(* Offset) += stringsize;

	return(1);
}
//..........................................................................................................................
template<int stringsize> int  MFD_String<stringsize>::WriteDefaultData(char * InBuf,unsigned long * Offset)
{
	if ( ((* Offset) + stringsize) >= MFINANCEDATA_MAX_SIZE )
	{
		return(-1);
	}

	memcpy(InBuf + (* Offset),m_Value,stringsize);
	(* Offset) += stringsize;

	return(1);
}
//--------------------------------------------------------------------------------------------------------------------------
//类型名称：以0结束的字符串[其中，必须指明最大长度]
//表示范围：没有范围
//匹配类型：char []
template<int stringsize> class MFD_ZeroString : public MFinanceBaseData
{
protected:
public:
	MFD_ZeroString(void);
	virtual ~MFD_ZeroString();
public:
	virtual void WriteDataToBuf(unsigned long * BitOffset);
	virtual void ReadDataFromBuf(unsigned long * BitOffset);
	virtual int  ReadDefaultData(unsigned long * Offset);
	virtual int  WriteDefaultData(char * InBuf,unsigned long * Offset);
public:
	virtual void operator = (char * In);
	void GetData(char * OutBuf);
};
//..........................................................................................................................
template<int stringsize> MFD_ZeroString<stringsize>::MFD_ZeroString(void)
{
	
}
//..........................................................................................................................
template<int stringsize> MFD_ZeroString<stringsize>::~MFD_ZeroString(void)
{
	
}
//..........................................................................................................................
template<int stringsize> void MFD_ZeroString<stringsize>::operator = (char * InBuf)
{
	inner_realloc(stringsize);
	
	strncpy(m_Value,InBuf,stringsize);
}
//..........................................................................................................................
template<int stringsize> void MFD_ZeroString<stringsize>::GetData(char * OutBuf)
{
	strncpy(OutBuf,m_Value,stringsize);
}
//..........................................................................................................................
template<int stringsize> void MFD_ZeroString<stringsize>::WriteDataToBuf(unsigned long * BitOffset)
{
	register int				errorcode = strlen(m_Value) + 1;
	inner_putbitstring(BitOffset,m_Value,min(stringsize,errorcode) * 8);
}
//..........................................................................................................................
template<int stringsize> void MFD_ZeroString<stringsize>::ReadDataFromBuf(unsigned long * BitOffset)
{
	register int					i = 0;
	unsigned long					errorcode;

	while ( i < (int)m_MaxValueSize )
	{
		inner_getbit(BitOffset,&errorcode,8);
		if ( errorcode == 0 )
		{
			m_Value[i] = 0;
			return;
		}
		else
		{
			m_Value[i] = (char)errorcode;
			i ++;
		}
	}
}
//..........................................................................................................................
template<int stringsize> int  MFD_ZeroString<stringsize>::ReadDefaultData(unsigned long * Offset)
{
	register int					i = 0;
	
	while ( i < (int)m_MaxValueSize && ((* Offset) < (m_MaxBitSize / 8)) )
	{
		if ( m_RecordData[* Offset] == 0 )
		{
			m_Value[i] = 0;

			(* Offset) ++;
			return(1);
		}
		else
		{
			m_Value[i] = (char)m_RecordData[* Offset];

			i ++;
			(* Offset) ++;
		}
	}

	if ( (* Offset) < (m_MaxBitSize / 8) )
	{
		return(1);
	}
	else
	{
		return(-1);
	}
}
//..........................................................................................................................
template<int stringsize> int  MFD_ZeroString<stringsize>::WriteDefaultData(char * InBuf,unsigned long * Offset)
{
	register int				errorcode = strlen(m_Value) + 1;

	if ( ((* Offset) + errorcode) >= MFINANCEDATA_MAX_SIZE )
	{
		return(-1);
	}

	memcpy(InBuf + (* Offset),m_Value,errorcode);
	(* Offset) += errorcode;

	return(1);
}
//--------------------------------------------------------------------------------------------------------------------------
class MFinanceData
{
protected:
	char				*	m_RecordData;
	char					m_DefaultData[MFINANCEDATA_MAX_SIZE];
	unsigned long			m_DefaultSize;
	bool					m_IsFinanceDataFlag;
	unsigned long			m_MaxRecord;
	unsigned long			m_CurBitSize;
	unsigned char			m_RemainBitSize;
public:
	MFinanceData(void);
	virtual ~MFinanceData();
public:
	void AttchBufToRead(char * InBuf,unsigned long InSize);
	void AttchBufToWrite(char * InBuf,unsigned long InSize);
public:
	int  ReadData(char * OutBuf,unsigned long InSize);
	int  WriteData(char * InBuf,unsigned long InSize);
public:
	int  GetCurSize(void);
};
//--------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------
