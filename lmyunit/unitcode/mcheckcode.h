//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMCheckCodeH__
#define __LmyUnitMCheckCodeH__
//--------------------------------------------------------------------------------------------------------------------------------
//公共头文件
#include "mobject.h"
#include "mstring.h"
#include <string> 
#include <stdlib.h>
using namespace std;
//................................................................................................................................
#ifdef WINDOWSCODE
//................................................................................................................................
//Windows操作系统
//................................................................................................................................
#else
//................................................................................................................................
//Linux操作系统
//................................................................................................................................
#endif
//--------------------------------------------------------------------------------------------------------------------------------
//CRC16位校验
class MCRC16 : public MObject
{
private:
public:
	MCRC16(void);
	virtual ~MCRC16();
public:
	unsigned short CheckCode(char * InBuf,unsigned short InSize);

	DECLARE_LMYUNIT(MCRC16)
};
//--------------------------------------------------------------------------------------------------------------------------------
//反码和的反码校验
class MConCheckCode : public MObject
{
private:
public:
	MConCheckCode(void);
	~MConCheckCode();
public:
	unsigned short CheckCode(char * InBuf,unsigned short InSize);

	DECLARE_LMYUNIT(MConCheckCode)
};
//--------------------------------------------------------------------------------------------------------------------------------
#define		ERROR_MMD5_NOMEMORY			(ERROR_USER(90))			//计算缓冲数据MD5摘要发生错误[没有足够的内存可以分配]
//................................................................................................................................
//MD5报文摘要算法
class MMD5 : public MObject
{
private:
    DWORD  F(DWORD x,DWORD y,DWORD z);
    DWORD  G(DWORD x,DWORD y,DWORD z);
    DWORD  H(DWORD x,DWORD y,DWORD z);
    DWORD  I(DWORD x,DWORD y,DWORD z);
    DWORD  ShrLoop(DWORD Value,unsigned char n);
    void   FF(DWORD &A,DWORD B,DWORD C,DWORD D,DWORD X,unsigned char S,DWORD T);
    void   GG(DWORD &A,DWORD B,DWORD C,DWORD D,DWORD X,unsigned char S,DWORD T);
    void   HH(DWORD &A,DWORD B,DWORD C,DWORD D,DWORD X,unsigned char S,DWORD T);
    void   II(DWORD &A,DWORD B,DWORD C,DWORD D,DWORD X,unsigned char S,DWORD T);
public:
    MMD5(void);
    ~MMD5();
public:
    int  MD5(const char * InBuf,int InSize,char OutBuf[16]);

	char 	*MD5(const char * inbuf,int insize);
	//string  MD5(const char * inbuf,int insize);
	//MString MD5(const char * inbuf,int insize);




	DECLARE_LMYUNIT(MMD5)
};
//--------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------
