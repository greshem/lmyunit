//--------------------------------------------------------------------------------------------------------------------------------
#include "mblockcompress.h"
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MBlockDataCompress,MObject)

	ERROR_DEFINE(ERROR_MBLOCKDATACOMPRESS_PARAM,"MBlockDataCompress","压缩数据错误[参数错误]")
	ERROR_DEFINE(ERROR_MBLOCKDATACOMPRESS_CANTDO,"MBlockDataCompress","压缩数据错误[不能压缩该数据]")

END_LMYUNIT
//..............................................................................................................................
MBlockDataCompress::MBlockDataCompress(void)
{

}
//..............................................................................................................................
MBlockDataCompress::~MBlockDataCompress()
{

}
//..............................................................................................................................
int  MBlockDataCompress::CompressBuf(char * InBuf,unsigned short Offset,unsigned short BlockSize,unsigned short BlockCount,char * OutBuf,unsigned short OutSize)
{
	register unsigned short							i;
	register unsigned short							j;
	register unsigned char							targetchar;
	register unsigned short							zerocount = 0;
	register unsigned short							outcount;
	register unsigned short							limitsize;
	unsigned char								*	inbufptr;
	unsigned char								*	outbufptr;
	unsigned char									oldchar = 0;

	if ( OutSize < (Offset + BlockSize * BlockCount) || OutSize <= 6 )
	{
		return(ERROR_MBLOCKDATACOMPRESS_PARAM);
	}

	limitsize = min(Offset + BlockSize * BlockCount,OutSize);
	memcpy(OutBuf,(char *)&Offset,sizeof(unsigned short));
	memcpy(OutBuf + sizeof(unsigned short),(char *)&BlockSize,sizeof(unsigned short));
	memcpy(OutBuf + sizeof(unsigned short) + sizeof(unsigned short),(char *)&BlockCount,sizeof(unsigned short));
	memcpy(OutBuf + sizeof(unsigned short) + sizeof(unsigned short) + sizeof(unsigned short),InBuf,Offset);

	outbufptr = (unsigned char *)OutBuf + 3 * sizeof(unsigned short) + Offset;
	outcount = 3 * sizeof(unsigned short) + Offset;

	for ( i=0;i<=BlockSize-1;i++ )
	{
		inbufptr = (unsigned char *)InBuf + Offset + i;

		for ( j=0;j<=BlockCount-1;j++ )
		{
			targetchar = (* inbufptr) - oldchar;
			oldchar = (* inbufptr);

			if ( targetchar == 0 )
			{
				zerocount ++;
				
				if ( zerocount >= 256 )
				{
					if ( (outcount + 1) < limitsize )
					{
						* outbufptr = 0;
						* (outbufptr + 1) = (unsigned char)(zerocount - 1);

						outbufptr += 2;
						outcount += 2;
						zerocount = 0;
					}
					else
					{
						return(ERROR_MBLOCKDATACOMPRESS_CANTDO);
					}
				}
			}
			else
			{
				if ( zerocount != 0 )
				{
					if ( (outcount + 1) < limitsize )
					{
						* outbufptr = 0;
						* (outbufptr + 1) = (unsigned char)(zerocount - 1);

						outbufptr += 2;
						outcount += 2;
						zerocount = 0;
					}
					else
					{
						return(ERROR_MBLOCKDATACOMPRESS_CANTDO);
					}
				}

				if ( outcount < limitsize )
				{
					* outbufptr = targetchar;
					outbufptr ++;
					outcount ++;
				}
				else
				{
					return(ERROR_MBLOCKDATACOMPRESS_CANTDO);
				}
			}
			
			inbufptr += BlockSize;
		}
	}

	if ( zerocount != 0 )
	{
		if ( (outcount + 1) < limitsize )
		{
			* outbufptr = 0;
			* (outbufptr + 1) = (unsigned char)(zerocount - 1);

			outbufptr += 2;
			outcount += 2;
			zerocount = 0;
		}
		else
		{
			return(ERROR_MBLOCKDATACOMPRESS_CANTDO);
		}
	}

	return(outcount);
}
//..............................................................................................................................
int  MBlockDataCompress::ExpandBuf(char * InBuf,unsigned short InSize,char * OutBuf,unsigned short OutSize)
{
	unsigned short									offset;
	unsigned short									blocksize;
	unsigned short									blockcount;
	register unsigned short							i,j;
	register unsigned char						*	inputptr;
	register unsigned char						*	outputptr;
	register unsigned short							zerocount;
	register unsigned short							outcount;
	register unsigned short							outoffset;
	register unsigned char							oldchar = 0;
	register unsigned char							targetchar;

	memcpy((char *)&offset,InBuf,sizeof(unsigned short));
	memcpy((char *)&blocksize,InBuf + sizeof(unsigned short),sizeof(unsigned short));
	memcpy((char *)&blockcount,InBuf + sizeof(unsigned short) + sizeof(unsigned short),sizeof(unsigned short));

	if ( OutSize < (offset + blocksize * blockcount) )
	{
		return(ERROR_MBLOCKDATACOMPRESS_PARAM);
	}

	memcpy(OutBuf,InBuf + 3 * sizeof(unsigned short),offset);

	inputptr = (unsigned char *)InBuf + 3 * sizeof(unsigned short) + offset;
	outputptr = (unsigned char *)OutBuf + offset;
	outcount = 0;
	outoffset = 0;

	i = 0;
	while ( i < (InSize - 3 * sizeof(unsigned short) - offset) )
	{
		targetchar = ( * inputptr ) + oldchar;
		oldchar = targetchar;

		if ( * inputptr == 0 )
		{
			zerocount = * (inputptr + 1);
			for ( j=0;j<=zerocount;j++ )
			{
				* outputptr = targetchar;
				outputptr += blocksize;
				outcount ++;

				if ( outcount >= blockcount )
				{
					outoffset ++;
					outcount = 0;
					outputptr = (unsigned char *)OutBuf + offset + outoffset;
				}
			}

			i += 2;
			inputptr += 2;
		}
		else
		{
			* outputptr = targetchar;
			outputptr += blocksize;
			outcount ++;

			if ( outcount >= blockcount )
			{
				outoffset ++;
				outcount = 0;
				outputptr = (unsigned char *)OutBuf + offset + outoffset;
			}

			i ++;
			inputptr ++;
		}
	}


	return(offset + blocksize * blockcount);
}
//--------------------------------------------------------------------------------------------------------------------------------
