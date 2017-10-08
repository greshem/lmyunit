//--------------------------------------------------------------------------------------------------------------------------------
//                  ;;;,
//        ,;;;;;: ,;;;:.,;..
//         :;;"`,;;;;;;"":;;					��Ԫ���ƣ�DES���ܴ���
//      ..;;:  .;;,.;;:',;;"
//    ,;;;;;;" :;`',;",;;"						��д���ڣ�2004��5��20
//   :" ,;:` , `:.;;;;;'
//    ,;;;,;:;;,;;;, ,;							��д��Ա��richtech
//   :;;;"` `:;;;;;,;,.;.
//   '""   .;;`.;";:;;;;` ;,					��ע��Ϣ��
//       .;"`  ::. '   .,;;;
//      ""     ';;;;;;;;;;`
//--------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMDESH__
#define __LmyUnitMDESH__
//--------------------------------------------------------------------------------------------------------------------------------
//����ͷ�ļ�
#include "mobject.h"
//................................................................................................................................
#ifdef WINDOWSCODE
//................................................................................................................................
//Windows����ϵͳ
//................................................................................................................................
#else
//................................................................................................................................
//Linux����ϵͳ
//................................................................................................................................
#endif
//--------------------------------------------------------------------------------------------------------------------------------
class MDES64 : public MObject
{
protected:
	void ByteToBit(char * InBuf,unsigned short BitCount,unsigned char * OutBuf);
	void BitToByte(unsigned char * InBuf,unsigned short BitCount,char * OutBuf);
	void TransForm(unsigned char * InBuf,unsigned short InSize,unsigned char * OutBuf,unsigned char * Table);
	void RotateL(unsigned char * InBuf,unsigned short InSize,unsigned char Loop);
	void XorFunction(unsigned char * InBuf,unsigned char * XorBuf,unsigned short InSize);
	void SFunction(unsigned char * InBuf,unsigned char * OutBuf);
	void FFunction(unsigned char * InBuf,unsigned char * KeyBuf);
protected:
	void CryptBlock(unsigned char * InBuf,unsigned char * OutBuf,char * Key,unsigned char Type);
public:
	MDES64(void);
	~MDES64();
public:
	int  EncryptBuf(char * InBuf,unsigned short InSize,char * OutBuf,char * Key);
	int  DecryptBuf(char * InBuf,unsigned short InSize,char * OutBuf,char * Key);

	DECLARE_LMYUNIT(MDES64)
};
//--------------------------------------------------------------------------------------------------------------------------------
class M3DES64 : public MDES64
{
private:
public:
	M3DES64(void);
	~M3DES64();
public:
	int  EncryptBuf(char * InBuf,unsigned short InSize,char * OutBuf,char * Key);
	int  DecryptBuf(char * InBuf,unsigned short InSize,char * OutBuf,char * Key);

	DECLARE_LMYUNIT(M3DES64)
};
//--------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------
