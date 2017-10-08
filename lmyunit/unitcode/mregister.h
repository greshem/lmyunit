//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMRegisterH__
#define __LmyUnitMRegisterH__
//--------------------------------------------------------------------------------------------------------------------------------
#ifdef WINDOWSCODE
//--------------------------------------------------------------------------------------------------------------------------------
#include "mobject.h"
//--------------------------------------------------------------------------------------------------------------------------------
class MRegister : public MObject
{
protected:
	HKEY						m_RootKey;
	HKEY						m_CurrentKey;
public:
	MRegister(void);
	virtual ~MRegister();
public:
	int  OpenKey(HKEY RootKey,MString Key);
    int  CreateKey(HKEY RootKey,MString Key);
    void CloseKey(void);
public:
    int  ReadString(MString Name,MString * Out);
	int  ReadString(MString Name,char * OutBuf,unsigned short InSize);
    int  WriteString(MString Name,MString In);

    int  ReadInteger(MString Name,unsigned long * Out);
    int  WriteString(MString  Name,unsigned long In);

    int  ReadBinary(MString Name,char * OutBuf,unsigned short InSize);
    int  WriteBinary(MString Name,char * InBuf,unsigned short InSize);

	DECLARE_LMYUNIT(MRegister)
};
//--------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------
