//--------------------------------------------------------------------------------------------------------------------------------
#include "mdes.h"
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MDES64,MObject)

END_LMYUNIT
//..............................................................................................................................
MDES64::MDES64(void)
{

}
//..............................................................................................................................
MDES64::~MDES64()
{

}
//..............................................................................................................................
void MDES64::ByteToBit(char * InBuf,unsigned short BitCount,unsigned char * OutBuf)
{
	register int								i;

	for ( i=0;i<=BitCount-1;i++ )
	{
		OutBuf[i] = ((unsigned char)InBuf[i>>3]>>(i&7)) & 1;
	}
}
//..............................................................................................................................
void MDES64::BitToByte(unsigned char * InBuf,unsigned short BitCount,char * OutBuf)
{
	register int								i;

	memset(OutBuf,0,BitCount>>3);
	for ( i=0;i<=BitCount-1;i++ )
	{
		OutBuf[i>>3] |= InBuf[i]<<(i&7);
	}
}
//..............................................................................................................................
void MDES64::TransForm(unsigned char * InBuf,unsigned short InSize,unsigned char * OutBuf,unsigned char * Table)
{
	register int								i;
	unsigned char								tempbuf[64];

	if ( InBuf == OutBuf )
	{
		for ( i=0;i<=InSize-1;i++ )
		{
			tempbuf[i] = InBuf[Table[i] - 1];
		}

		memcpy(OutBuf,tempbuf,InSize);
	}
	else
	{
		for ( i=0;i<=InSize-1;i++ )
		{
			OutBuf[i] = InBuf[Table[i] - 1];
		}
	}
}
//..............................................................................................................................
void MDES64::RotateL(unsigned char * InBuf,unsigned short InSize,unsigned char Loop)
{
	unsigned char								tempbuf[64];

	memcpy(tempbuf,InBuf,Loop);
	memmove(InBuf,InBuf + Loop,InSize - Loop);
	memcpy(InBuf + InSize - Loop,tempbuf,Loop);
}
//..............................................................................................................................
void MDES64::XorFunction(unsigned char * InBuf,unsigned char * XorBuf,unsigned short InSize)
{
	register int								i;

	for ( i=0;i<=InSize-1;i++ )
	{
		InBuf[i] = InBuf[i] ^ XorBuf[i];
	}
}
//..............................................................................................................................
void MDES64::SFunction(unsigned char * InBuf,unsigned char * OutBuf)
{
	unsigned char						stable[8][4][16] = {	// S1 
																14,	 4,	13,	 1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
																 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
																 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
																15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13,
																// S2 
																15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
																 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
																 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
																13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9,
																// S3 
																10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
																13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
																13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
																 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12,
																// S4 
																 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
																13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
																10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
																 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14,
																// S5 
																 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
																14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
																 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
																11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3,
																// S6 
																12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
																10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
																 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
																 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13,
																// S7 
																 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
																13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
																 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
																 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12,
																// S8 
																13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
																 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
																 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
																 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11	};
	unsigned short						x,y;
	register int						i;
	unsigned char						* in,* out;
	unsigned char						errorcode;

	in = InBuf;
	out = OutBuf;

	for ( i=0;i<=7;i++ )
	{
		x = (in[0] << 1) | in[5];
		y = (in[1] << 3) | (in[2] << 2) | (in[3] << 1) | in[4];
		errorcode = stable[i][x][y];
		ByteToBit((char *)&errorcode,4,out);

		in += 6;
		out += 4;
	}
}
//..............................................................................................................................
void MDES64::FFunction(unsigned char * InBuf,unsigned char * KeyBuf)
{
	unsigned char						etable[48] = {			32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
																 8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
																16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
																24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1	};
	unsigned char						ptable[32] = {			16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 23, 26, 5,  18, 31, 10,
																2,  8, 24, 14, 32, 27, 3,  9,  19, 13, 30, 6,  22, 11, 4,  25	};
	unsigned char						tempbuf[48];
	unsigned char						outbuf[32];

	TransForm(InBuf,48,tempbuf,etable);
	
	XorFunction(tempbuf,KeyBuf,48);
	SFunction(tempbuf,outbuf);
	TransForm(outbuf,32,InBuf,ptable);
}
//..............................................................................................................................
void MDES64::CryptBlock(unsigned char * InBuf,unsigned char * OutBuf,char * Key,unsigned char Type)
{
	unsigned char						keyip_1table[56] = {	57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
																10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
																63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
																14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4	};
	unsigned char						keyip_2table[48] = {	14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
																23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
																41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
																44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32	};
	unsigned char						keyleftloop[16] = {		1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1	};

	unsigned char						iptable[64] = {			58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
																62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
																57, 49, 41, 33, 25, 17,  9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
																61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7	};
	unsigned char						iprtable[64] = {		40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
																38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
																36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
																34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41,  9, 49, 17, 57, 25	};
	char								keysource[8];
	unsigned char						keymap[16][48];
	unsigned char						keybuf[64],* keyleft,* keyright;
	register int						i;
	unsigned char						* leftptr,* rightptr;
	unsigned char						tempbuf[32];
	
	//生成加密循环的密匙
	memset(keysource,0,8);
	strncpy(keysource,Key,8);
	ByteToBit(Key,64,keybuf);
	TransForm(keybuf,56,keybuf,keyip_1table);
	keyleft = &keybuf[0];
	keyright = &keybuf[28];
	for ( i=0;i<=15;i++ )
	{
		RotateL(keyleft,28,keyleftloop[i]);
		RotateL(keyright,28,keyleftloop[i]);
		TransForm(keybuf,48,keymap[i],keyip_2table);
	}

	//置换原文缓冲
	leftptr = &InBuf[0];
	rightptr = &InBuf[32];
	TransForm(InBuf,64,InBuf,iptable);
	
	if ( Type == 0 )
	{
		//加密
		for ( i=0;i<=15;i++ )
		{
			memcpy(tempbuf,rightptr,32);
			FFunction(rightptr,keymap[i]);
			XorFunction(rightptr,leftptr,32);
			memcpy(leftptr,tempbuf,32);
		}
	}
	else
	{
		//解密
		for ( i=0;i<=15;i++ )
		{
			memcpy(tempbuf,leftptr,32);
			FFunction(leftptr,keymap[15-i]);
			XorFunction(leftptr,rightptr,32);
			memcpy(rightptr,tempbuf,32);
		}
	}
	
	TransForm(InBuf,64,OutBuf,iprtable);
}
//..............................................................................................................................
int  MDES64::EncryptBuf(char * InBuf,unsigned short InSize,char * OutBuf,char * Key)
{
	register int									i;
	unsigned char									blockbuf[64];
	unsigned char									tempbuf[64];
	char											keybuf[8];

	memcpy(keybuf,Key,7);
	keybuf[7] = 0;
	for ( i=0;i<=6;i++ )
	{
		keybuf[7] += keybuf[i];
	}

	if ( (InSize % 8) != 0 )
	{
		memcpy( OutBuf + ((InSize>>3)<<3),InBuf + ((InSize>>3)<<3),InSize % 8);
	}

	for ( i=0;i<=(InSize>>3)-1;i++ )
	{
		ByteToBit(InBuf + (i << 3),64,blockbuf);
		CryptBlock(blockbuf,tempbuf,keybuf,0);
		BitToByte(tempbuf,64,OutBuf + (i << 3));
	}

	return(InSize);
}
//..............................................................................................................................
int  MDES64::DecryptBuf(char * InBuf,unsigned short InSize,char * OutBuf,char * Key)
{
	register int									i;
	unsigned char									blockbuf[64];
	unsigned char									tempbuf[64];
	char											keybuf[8];

	memcpy(keybuf,Key,7);
	keybuf[7] = 0;
	for ( i=0;i<=6;i++ )
	{
		keybuf[7] += keybuf[i];
	}

	if ( (InSize % 8) != 0 )
	{
		memcpy( OutBuf + ((InSize>>3)<<3),InBuf + ((InSize>>3)<<3),InSize % 8);
	}

	for ( i=0;i<=(InSize>>3)-1;i++ )
	{
		ByteToBit(InBuf + (i << 3),64,blockbuf);
		CryptBlock(blockbuf,tempbuf,keybuf,1);
		BitToByte(tempbuf,64,OutBuf + (i << 3));
	}

	return(InSize);
}
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(M3DES64,MDES64)

END_LMYUNIT
//..............................................................................................................................
M3DES64::M3DES64(void)
{

}
//..............................................................................................................................
M3DES64::~M3DES64()
{

}
//..............................................................................................................................
int  M3DES64::EncryptBuf(char * InBuf,unsigned short InSize,char * OutBuf,char * Key)
{
	char										*	key1,* key2;
	unsigned char									blockbuf[64];
	unsigned char									tempbuf[64];
	register int									i;
	char											keybuf[16];

	memcpy(keybuf,Key,7);
	memcpy(keybuf + 8,Key + 7,7);

	keybuf[7] = 0;
	keybuf[15] = 0;

	for ( i=0;i<=6;i++ )
	{
		keybuf[7] += keybuf[i];
		keybuf[15] += keybuf[8+i];
	}

	key1 = &keybuf[0];
	key2 = &keybuf[8];

	for ( i=0;i<=(InSize>>3)-1;i++ )
	{
		ByteToBit(InBuf + (i << 3),64,blockbuf);
		CryptBlock(blockbuf,tempbuf,key1,1);
		CryptBlock(tempbuf,blockbuf,key2,0);
		CryptBlock(blockbuf,tempbuf,key1,1);
		BitToByte(tempbuf,64,OutBuf + (i << 3));
	}

	return(InSize);
}
//..............................................................................................................................
int  M3DES64::DecryptBuf(char * InBuf,unsigned short InSize,char * OutBuf,char * Key)
{
	char										*	key1,* key2;
	unsigned char									blockbuf[64];
	unsigned char									tempbuf[64];
	register int									i;
		char											keybuf[16];

	memcpy(keybuf,Key,7);
	memcpy(keybuf + 8,Key + 7,7);

	keybuf[7] = 0;
	keybuf[15] = 0;

	for ( i=0;i<=6;i++ )
	{
		keybuf[7] += keybuf[i];
		keybuf[15] += keybuf[8+i];
	}

	key1 = &keybuf[0];
	key2 = &keybuf[8];

	for ( i=0;i<=(InSize>>3)-1;i++ )
	{
		ByteToBit(InBuf + (i << 3),64,blockbuf);
		CryptBlock(blockbuf,tempbuf,key1,0);
		CryptBlock(tempbuf,blockbuf,key2,1);
		CryptBlock(blockbuf,tempbuf,key1,0);
		BitToByte(tempbuf,64,OutBuf + (i << 3));
	}

	return(InSize);
}
//--------------------------------------------------------------------------------------------------------------------------------
