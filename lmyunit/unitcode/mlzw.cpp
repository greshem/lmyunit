//--------------------------------------------------------------------------------------------------------------------------------
#include "mlzw.h"
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MLZW4096,MObject)

	ERROR_DEFINE(ERROR_MLZW4096_INSIDEPARAM,"MLZW4096","压缩数据发生错误[内部参数错误]")

END_LMYUNIT
//..............................................................................................................................
MLZW4096::MLZW4096(void)
{

}
//..............................................................................................................................
MLZW4096::~MLZW4096()
{

}
//..............................................................................................................................
int  MLZW4096::PutBitToBuf(char * InBuf,unsigned short InSize,unsigned long BitOffset,unsigned long Value,unsigned long BitSize)
{
	register unsigned long								byteoffset;
	register unsigned long								bytestart;

	byteoffset = BitOffset >> 3;
	bytestart = BitOffset - ( (BitOffset >> 3) << 3 );

	if ( byteoffset >= InSize )
	{
		return(ERROR_MLZW4096_INSIDEPARAM);
	}

	if ( ( 8 - bytestart ) >= BitSize )
	{
		InBuf[byteoffset] = (unsigned char)(InBuf[byteoffset] | ( Value << ( 8 - bytestart - BitSize ) ));
		return(1);
	}
	else
	{
		InBuf[byteoffset] = (unsigned char)(InBuf[byteoffset] | ( Value >> ( BitSize - 8 + bytestart ) ));

		BitOffset += 8 - bytestart;
		BitSize -= 8 - bytestart;
		Value = Value & ( 0xFFFFFFFF >> (32 - BitSize) );
		return(PutBitToBuf(InBuf,InSize,BitOffset,Value,BitSize));
	}
}
//..............................................................................................................................
int  MLZW4096::GetBitFromBuf(char * InBuf,unsigned short InSize,unsigned long BitOffset,unsigned long * Value,unsigned long BitSize)
{
	register unsigned long									byteoffset;
	register unsigned long									bytestart;
	register unsigned char									invalue;
	register unsigned long									tempvalue;
	register int											errorcode;

	* Value = 0;
	byteoffset = BitOffset >> 3;
	bytestart = BitOffset - ( (BitOffset >> 3) << 3 );

	if ( byteoffset >= InSize )
	{
		return(ERROR_MLZW4096_INSIDEPARAM);
	}

	if ( ( 8 - bytestart ) >= BitSize )
	{
		invalue = InBuf[byteoffset];
		* Value = (unsigned long)((invalue & ( 0xFF >> bytestart )) >> ( 8 - bytestart - BitSize ));

		return(1);
	}
	else
	{
		invalue = InBuf[byteoffset];
		* Value = (invalue & ( 0xFF >> bytestart ));

		BitOffset += 8 - bytestart;
		BitSize -= 8 - bytestart;

		if ( (errorcode = GetBitFromBuf(InBuf,InSize,BitOffset,&tempvalue,BitSize)) < 0 )
		{
			return(errorcode);
		}

		* Value = (( * Value ) << BitSize) | tempvalue;
		return(1);
	}
}
//..............................................................................................................................
void MLZW4096::Initialize(void)
{
	register int								i;

	for ( i=0;i<=MLZW4096_TABLESIZE-1;i++ )
	{
		m_Dictory[i].CodeValue = MLZW4096_UNUSER;
		m_Dictory[i].ParentCode = 0;
		m_Dictory[i].Character = 0;
	}
}
//..............................................................................................................................
unsigned long  MLZW4096::FindChildNode(long ParentCode,long ChildCode)
{
	register unsigned long						index;
	register long								offset;

	index = ( ChildCode << ( MLZW4096_BITS - 8) ) ^ ParentCode;
	if ( index == 0 )
	{
		offset = 1;
	}
	else
	{
		offset = MLZW4096_TABLESIZE - index;
	}

	while ( 1 )
	{
		if ( m_Dictory[index].CodeValue == MLZW4096_UNUSER )
		{
			return(index);
		}

		if ( m_Dictory[index].ParentCode == (short)ParentCode && m_Dictory[index].Character == (char)ChildCode )
		{
			return(index);
		}

		if ( (int)index >= offset )
		{
			index -= offset;
		}
		else
		{
			index += MLZW4096_TABLESIZE - offset;
		}
	}
}
//..............................................................................................................................
int  MLZW4096::CompressBuf(char * InBuf,unsigned short InSize,char * OutBuf,unsigned short OutSize)
{
	register int											stringcode;
	register int											inputptr = 1;
	register unsigned long									index;
	register int											charecter;
	register int											nextcode = MLZW4096_FIRSTCODE;
	register unsigned long									outbitptr = 0;
	register unsigned long									outbitsize = 9;
	register int											nextbumpsize = 512;
	register unsigned short									limitsize;
	unsigned char										*	inbuf;
	register int											errorcode;

	inbuf = (unsigned char *)InBuf;
	Initialize();
	memset(OutBuf,0,OutSize);
	limitsize = min(OutSize,InSize);

	stringcode = (int)inbuf[0];
	while ( inputptr < InSize )
	{
		charecter = (int)inbuf[inputptr];
		index = FindChildNode(stringcode,charecter);
		
		if ( m_Dictory[index].CodeValue != MLZW4096_UNUSER )
		{
			stringcode = (long)m_Dictory[index].CodeValue;
		}
		else
		{
			m_Dictory[index].CodeValue = (short)nextcode;
			m_Dictory[index].ParentCode = (short)stringcode;
			m_Dictory[index].Character = (char)charecter;

			if ( (errorcode = PutBitToBuf(OutBuf,limitsize,outbitptr,stringcode,outbitsize)) < 0 )
			{
				return(errorcode);
			}

			nextcode ++;
			stringcode = charecter;
			outbitptr += outbitsize;

			if ( nextcode >= nextbumpsize )
			{
				if ( (errorcode = PutBitToBuf(OutBuf,limitsize,outbitptr,(unsigned long)MLZW4096_BUMPCODE,outbitsize)) < 0 )
				{
					return(errorcode);
				}

				outbitptr += outbitsize;
				
				outbitsize ++;
				nextbumpsize = nextbumpsize << 1;
			}
		}

		inputptr ++;
	}

	if ( (errorcode = PutBitToBuf(OutBuf,limitsize,outbitptr,stringcode,outbitsize)) < 0 )
	{
		return(errorcode);
	}

	if ( (errorcode = PutBitToBuf(OutBuf,limitsize,outbitptr + outbitsize,MLZW4096_END,outbitsize)) < 0 )
	{
		return(errorcode);
	}

	outbitptr += outbitsize + outbitsize;

	if ( (outbitptr % 8) != 0 )
	{
		return((outbitptr >> 3) + 1);
	}
	else
	{
		return(outbitptr >> 3);
	}
}
//..............................................................................................................................
unsigned long MLZW4096::DecodeString(unsigned long Count,unsigned long Code)
{
	while ( Code > 255 )
	{
		if ( Count >= MLZW4096_TABLESIZE || Code >= MLZW4096_TABLESIZE )
		{
			return(ERROR_MLZW4096_INSIDEPARAM);
		}
		m_StackBuf[Count] = m_Dictory[Code].Character;
		Code = (short)m_Dictory[Code].ParentCode;
		Count ++;
	}

	m_StackBuf[Count] = (char)Code;
	Count ++;

	return(Count);
}
//..............................................................................................................................
int  MLZW4096::ExpandBuf(char * InBuf,unsigned short InSize,char * OutBuf,unsigned short OutSize)
{
	register unsigned long								oldcode;
	register unsigned long								newcode;
	register int										nextcode = MLZW4096_FIRSTCODE;
	register unsigned long								count;
	register int										character;
	register unsigned short								outptr = 1;
	register unsigned long								inbitptr = 9;
	register unsigned long								inbitsize = 9;
	register int										errorcode;

	if ( (errorcode = GetBitFromBuf(InBuf,InSize,0,&oldcode,9)) < 0 )
	{
		return(errorcode);
	}

	OutBuf[0] = (char)oldcode;
	character = (char)oldcode;

	while ( (errorcode = GetBitFromBuf(InBuf,InSize,inbitptr,&newcode,inbitsize)) > 0 )
	{
		if ( newcode == MLZW4096_END )
		{
			return(outptr);
		}

		if ( newcode == MLZW4096_BUMPCODE )
		{
			inbitptr += inbitsize;
			inbitsize ++;
			continue;
		}
		
		inbitptr += inbitsize;

		if ( (int)newcode >= nextcode )
		{
			m_StackBuf[0] = (char)character;
			count = DecodeString(1,oldcode);
		}
		else
		{
			count = DecodeString(0,newcode);
		}

		if ( count < 0 )
		{
			return(ERROR_MLZW4096_INSIDEPARAM);
		}

		character = m_StackBuf[count-1];

		while ( count > 0 )
		{
			if ( outptr >= OutSize )
			{
				return(ERROR_MLZW4096_INSIDEPARAM);
			}

			OutBuf[outptr] = m_StackBuf[count-1];
			count --;
			outptr ++;
		}

		m_Dictory[nextcode].ParentCode = (short)oldcode;
		m_Dictory[nextcode].Character = (char)character;
		nextcode ++;

		oldcode = newcode;
	}

	return(errorcode);

}
//--------------------------------------------------------------------------------------------------------------------------------
