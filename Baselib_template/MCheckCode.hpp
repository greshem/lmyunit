#ifndef __LmyUnitMCheckCodeH__
#define __LmyUnitMCheckCodeH__

//#####################################################################################
//CRC16位校验
template <typename T> class MCRC16// : public MObject
{
private:
public:
	MCRC16(void);
	virtual ~MCRC16();
public:
	unsigned short CheckCode(char * InBuf,unsigned short InSize);

//	DECLARE_LMYUNIT(MCRC16)
};

//#####################################################################################
template <typename T> MCRC16<T>::MCRC16(void)
{

}
//#####################################################################################
template <typename T> MCRC16<T>::~MCRC16()
{

}
//#####################################################################################
 template <typename T> unsigned short MCRC16<T>::CheckCode(char * InBuf,unsigned short InSize)
{
unsigned short		crctable[256] = {	0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
										0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
										0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
										0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
										0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
										0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
										0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
										0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
										0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
										0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
										0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
										0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
										0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
										0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
										0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
										0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
										0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
										0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
										0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
										0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
										0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
										0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
										0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
										0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
										0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
										0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
										0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
										0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
										0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
										0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
										0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
										0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0	};
	register unsigned short						errorcode = 0;
	register int								i;

	for ( i=0;i<=InSize-1;i++ )
	{
		errorcode = crctable[((errorcode >> 8) & 0xff ) ^ ( InBuf[i] & 0xff )] ^ (errorcode << 8);
	}

	return(errorcode);
}
//#####################################################################################
//#####################################################################################
//反码和的反码校验
template < typename T> class MConCheckCode// : public MObject
{
private:
public:
	MConCheckCode(void);
	~MConCheckCode();
public:
	unsigned short CheckCode(char * InBuf,unsigned short InSize);

//	DECLARE_LMYUNIT(MConCheckCode)
};

//#####################################################################################
 template <typename T> MConCheckCode<T>::MConCheckCode(void)
{

}
//#####################################################################################
 template <typename T> MConCheckCode<T>::~MConCheckCode()
{

}

//#####################################################################################
 template <typename T> unsigned short MConCheckCode<T>::CheckCode(char * InBuf,unsigned short InSize)
{
	unsigned long						errorcode = 0;
	unsigned short					*	tempptr;

	tempptr = (unsigned short *)InBuf;
	while ( InSize > 1 )
	{
		errorcode += * tempptr ++;
		InSize -= sizeof(unsigned short);
	}

	if ( InSize > 0 )
	{
		errorcode += *(unsigned char *)tempptr;
	}

	errorcode = (errorcode >> 16) + (errorcode & 0xFFFF);
	errorcode += (errorcode >> 16);

	return((unsigned short)(~errorcode));
}

//#####################################################################################
//#####################################################################################
//MD5报文摘要算法
template <typename TT> class MMD5 
{
private:
    unsigned long  F(unsigned long x,unsigned long y,unsigned long z);
    unsigned long  G(unsigned long x,unsigned long y,unsigned long z);
    unsigned long  H(unsigned long x,unsigned long y,unsigned long z);
    unsigned long  I(unsigned long x,unsigned long y,unsigned long z);
    unsigned long  ShrLoop(unsigned long Value,unsigned char n);
    void   FF(unsigned long &A,unsigned long B,unsigned long C,unsigned long D,unsigned long X,unsigned char S,unsigned long T);
    void   GG(unsigned long &A,unsigned long B,unsigned long C,unsigned long D,unsigned long X,unsigned char S,unsigned long T);
    void   HH(unsigned long &A,unsigned long B,unsigned long C,unsigned long D,unsigned long X,unsigned char S,unsigned long T);
    void   II(unsigned long &A,unsigned long B,unsigned long C,unsigned long D,unsigned long X,unsigned char S,unsigned long T);
public:
    MMD5(void);
    ~MMD5();
public:
    int  MD5(const char * InBuf,int InSize,char OutBuf[16]);
    string  MD5(const char * InBuf,int InSize);

};
//#####################################################################################
 template <typename TT>MMD5<TT>::MMD5(void)
{

}
//#####################################################################################
 template <typename TT> MMD5<TT>::~MMD5()
{

}
//#####################################################################################
 template <typename TT> unsigned long  MMD5<TT>::F(unsigned long x,unsigned long y,unsigned long z)
{
    return((x & y) | ((~x) & z));
}
//#####################################################################################
 template <typename TT>unsigned long  MMD5<TT>::G(unsigned long x,unsigned long y,unsigned long z)
{
    return((x & z) | (y & (~z)));
}
//#####################################################################################
 template <typename TT>unsigned long  MMD5<TT>::H(unsigned long x,unsigned long y,unsigned long z)
{
    return(x ^ y ^ z);
}
//#####################################################################################
 template <typename TT>unsigned long  MMD5<TT>::I(unsigned long x,unsigned long y,unsigned long z)
{
    return(y ^ (x | (~z)));
}
//#####################################################################################
 template <typename TT>unsigned long  MMD5<TT>::ShrLoop(unsigned long Value,unsigned char n)
{
    return((Value << n) | (Value >> (32-n)));
}
//#####################################################################################
 template <typename TT>void  MMD5<TT>::FF(unsigned long &A,unsigned long B,unsigned long C,unsigned long D,unsigned long X,unsigned char S,unsigned long T)
{
    A = A + F(B,C,D) + X + T;
    A = ShrLoop(A,S);
    A = A + B;
}
//#####################################################################################
 template <typename TT>void  MMD5<TT>::GG(unsigned long &A,unsigned long B,unsigned long C,unsigned long D,unsigned long X,unsigned char S,unsigned long T)
{
    A = A + G(B,C,D) + X + T;
    A = ShrLoop(A,S);
    A = A + B;
}
//#####################################################################################
 template <typename TT>void  MMD5<TT>::HH(unsigned long &A,unsigned long B,unsigned long C,unsigned long D,unsigned long X,unsigned char S,unsigned long T)
{
    A = A + H(B,C,D) + X + T;
    A = ShrLoop(A,S);
    A = A + B;
}
//#####################################################################################
 template <typename TT> void  MMD5<TT>::II(unsigned long &A,unsigned long B,unsigned long C,unsigned long D,unsigned long X,unsigned char S,unsigned long T)
{
    A = A + I(B,C,D) + X + T;
    A = ShrLoop(A,S);
    A = A + B;
}
//#####################################################################################
 template <typename TT> int  MMD5<TT>::MD5(const char * InBuf,int InSize,char OutBuf[16])
{
    char                *   ExtentBuf;
	char					StaticBuf[4152];
    int                     ExtentSize;
    int                     TempInt;
    register int            i;
    unsigned long                   a,b,c,d;
    unsigned long                   AA,BB,CC,DD;
    unsigned long               *   X;

	assert(InBuf != NULL);
	assert(OutBuf != NULL);

    AA = 0x67452301;
    BB = 0xefcdab89;
    CC = 0x98badcfe;
    DD = 0x10325476;

    if ( InSize % 64 < 56 )
        ExtentSize = ( InSize / 64 ) * 64 + 64;
    else
        ExtentSize = ( InSize / 64 + 1 )  * 64 + 64;


	if ( ExtentSize > 4152 )
	{
		ExtentBuf = new char[ExtentSize];
		if ( ExtentBuf == NULL )
		{
			//没有足够的内存可以分配
//			return(ERROR_MMD5_NOMEMORY);
			return -1;
		}
	}
	else
	{
		ExtentBuf = StaticBuf;
	}

    memcpy(ExtentBuf,InBuf,InSize);

    for ( i=InSize;i<=ExtentSize-9;i++ )
    {
        if ( i == InSize )  ExtentBuf[i] = (unsigned char)128;
        else    ExtentBuf[i] = 0;
    }
    TempInt = InSize * 8;
    memcpy((char *)&ExtentBuf[ExtentSize-8],(char *)&TempInt,4);
    memset((char *)&ExtentBuf[ExtentSize-4],0x00,4);

    for (i=0;i<=ExtentSize/64-1;i++ )
    {
        a = AA;
        b = BB;
        c = CC;
        d = DD;

        X = (unsigned long *)&ExtentBuf[i * 64];

        FF (a, b, c, d, X[ 0],  7, 0xd76aa478); /* 1 */
        FF (d, a, b, c, X[ 1], 12, 0xe8c7b756); /* 2 */
        FF (c, d, a, b, X[ 2], 17, 0x242070db); /* 3 */
        FF (b, c, d, a, X[ 3], 22, 0xc1bdceee); /* 4 */
        FF (a, b, c, d, X[ 4],  7, 0xf57c0faf); /* 5 */
        FF (d, a, b, c, X[ 5], 12, 0x4787c62a); /* 6 */
        FF (c, d, a, b, X[ 6], 17, 0xa8304613); /* 7 */
        FF (b, c, d, a, X[ 7], 22, 0xfd469501); /* 8 */
        FF (a, b, c, d, X[ 8],  7, 0x698098d8); /* 9 */
        FF (d, a, b, c, X[ 9], 12, 0x8b44f7af); /* 10 */
        FF (c, d, a, b, X[10], 17, 0xffff5bb1); /* 11 */
        FF (b, c, d, a, X[11], 22, 0x895cd7be); /* 12 */
        FF (a, b, c, d, X[12],  7, 0x6b901122); /* 13 */
        FF (d, a, b, c, X[13], 12, 0xfd987193); /* 14 */
        FF (c, d, a, b, X[14], 17, 0xa679438e); /* 15 */
        FF (b, c, d, a, X[15], 22, 0x49b40821); /* 16 */

        GG (a, b, c, d, X[ 1],  5, 0xf61e2562); /* 17 */
        GG (d, a, b, c, X[ 6],  9, 0xc040b340); /* 18 */
        GG (c, d, a, b, X[11], 14, 0x265e5a51); /* 19 */
        GG (b, c, d, a, X[ 0], 20, 0xe9b6c7aa); /* 20 */
        GG (a, b, c, d, X[ 5],  5, 0xd62f105d); /* 21 */
        GG (d, a, b, c, X[10],  9,  0x2441453); /* 22 */
        GG (c, d, a, b, X[15], 14, 0xd8a1e681); /* 23 */
        GG (b, c, d, a, X[ 4], 20, 0xe7d3fbc8); /* 24 */
        GG (a, b, c, d, X[ 9],  5, 0x21e1cde6); /* 25 */
        GG (d, a, b, c, X[14],  9, 0xc33707d6); /* 26 */
        GG (c, d, a, b, X[ 3], 14, 0xf4d50d87); /* 27 */
        GG (b, c, d, a, X[ 8], 20, 0x455a14ed); /* 28 */
        GG (a, b, c, d, X[13],  5, 0xa9e3e905); /* 29 */
        GG (d, a, b, c, X[ 2],  9, 0xfcefa3f8); /* 30 */
        GG (c, d, a, b, X[ 7], 14, 0x676f02d9); /* 31 */
        GG (b, c, d, a, X[12], 20, 0x8d2a4c8a); /* 32 */

        HH (a, b, c, d, X[ 5],  4, 0Xfffa3942); /* 33 */
        HH (d, a, b, c, X[ 8], 11, 0X8771f681); /* 34 */
        HH (c, d, a, b, X[11], 16, 0X6d9d6122); /* 35 */
        HH (b, c, d, a, X[14], 23, 0Xfde5380c); /* 36 */
        HH (a, b, c, d, X[ 1],  4, 0Xa4beea44); /* 37 */
        HH (d, a, b, c, X[ 4], 11, 0X4bdecfa9); /* 38 */
        HH (c, d, a, b, X[ 7], 16, 0Xf6bb4b60); /* 39 */
        HH (b, c, d, a, X[10], 23, 0Xbebfbc70); /* 40 */
        HH (a, b, c, d, X[13],  4, 0X289b7ec6); /* 41 */
        HH (d, a, b, c, X[ 0], 11, 0Xeaa127fa); /* 42 */
        HH (c, d, a, b, X[ 3], 16, 0Xd4ef3085); /* 43 */
        HH (b, c, d, a, X[ 6], 23,  0X4881d05); /* 44 */
        HH (a, b, c, d, X[ 9],  4, 0Xd9d4d039); /* 45 */
        HH (d, a, b, c, X[12], 11, 0Xe6db99e5); /* 46 */
        HH (c, d, a, b, X[15], 16, 0X1fa27cf8); /* 47 */
        HH (b, c, d, a, X[ 2], 23, 0Xc4ac5665); /* 48 */

        II (a, b, c, d, X[ 0],  6, 0xf4292244); /* 49 */
        II (d, a, b, c, X[ 7], 10, 0X432aff97); /* 50 */
        II (c, d, a, b, X[14], 15, 0Xab9423a7); /* 51 */
        II (b, c, d, a, X[ 5], 21, 0Xfc93a039); /* 52 */
        II (a, b, c, d, X[12],  6, 0X655b59c3); /* 53 */
        II (d, a, b, c, X[ 3], 10, 0X8f0ccc92); /* 54 */
        II (c, d, a, b, X[10], 15, 0Xffeff47d); /* 55 */
        II (b, c, d, a, X[ 1], 21, 0X85845dd1); /* 56 */
        II (a, b, c, d, X[ 8],  6, 0X6fa87e4f); /* 57 */
        II (d, a, b, c, X[15], 10, 0Xfe2ce6e0); /* 58 */
        II (c, d, a, b, X[ 6], 15, 0Xa3014314); /* 59 */
        II (b, c, d, a, X[13], 21, 0X4e0811a1); /* 60 */
        II (a, b, c, d, X[ 4],  6, 0Xf7537e82); /* 61 */
        II (d, a, b, c, X[11], 10, 0Xbd3af235); /* 62 */
        II (c, d, a, b, X[ 2], 15, 0X2ad7d2bb); /* 63 */
        II (b, c, d, a, X[ 9], 21, 0Xeb86d391); /* 64 */
        
        AA += a;
        BB += b;
        CC += c;
        DD += d;
    }

	if ( ExtentBuf != StaticBuf )
	{
		delete [] ExtentBuf;
	}

    memcpy(OutBuf,(char *)&AA,4);
    memcpy(OutBuf + 4,(char *)&BB,4);
    memcpy(OutBuf + 8,(char *)&CC,4);
    memcpy(OutBuf + 12,(char *)&DD,4);

    return(1);
}
//template <typename TT> int  MMD5<TT>::MD5(const char * InBuf,int InSize,char OutBuf[16])
template <typename TT> string  MMD5<TT>::MD5(const char * InBuf,int InSize)
{
	unsigned char tmp[16];
	char buffer[256];
	
	memset(tmp, '\0', sizeof(tmp));
	memset(buffer, '\0', sizeof(buffer));
	MD5(InBuf, InSize,  (char *)tmp);
	int ret=0;
	for(int i=0; i<=15; i++)
	{
		ret+=sprintf(buffer+ret, "%2.2x", tmp[i]);
		//printf("%d\n", ret);
		//printf("%2.2x\n", tmp[i]);
	}
	buffer[32]='\0';
	//printf("%s\n", buffer);
	return string(buffer);
}
//#####################################################################################
#endif
