//--------------------------------------------------------------------------------------------------------------------------------
#include "mregister.h"
//--------------------------------------------------------------------------------------------------------------------------------
#ifdef WINDOWSCODE
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MRegister,MObject)

END_LMYUNIT
//................................................................................................................................
MRegister::MRegister(void)
{
	m_RootKey = NULL;
    m_CurrentKey = NULL;
}
//................................................................................................................................
MRegister::~MRegister()
{
	CloseKey();
}
//................................................................................................................................
int  MRegister::OpenKey(HKEY RootKey,MString Key)
{
	if ( ::RegOpenKey(RootKey,Key.c_str(),&m_CurrentKey) != ERROR_SUCCESS )
    {
        m_CurrentKey = NULL;
        return(ERROR_SYSTEM(::GetLastError()));
    }

    m_RootKey = RootKey;
    return(1);
}
//................................................................................................................................
int  MRegister::CreateKey(HKEY RootKey,MString Key)
{
	if ( ::RegCreateKey(RootKey,Key.c_str(),&m_CurrentKey) != ERROR_SUCCESS )
    {
        m_CurrentKey = NULL;
        return(ERROR_SYSTEM(::GetLastError()));
    }

    m_RootKey = RootKey;
    return(1);
}
//................................................................................................................................
void MRegister::CloseKey(void)
{
	if ( m_CurrentKey != NULL )
    {
        ::RegCloseKey(m_CurrentKey);
        m_CurrentKey = NULL;
    }
    m_RootKey = NULL;
}
//................................................................................................................................
int  MRegister::ReadString(MString Name,MString * Out)
{
	char									tempbuf[256];
	register unsigned long					errorcode = 256;

	if ( ::RegQueryValueEx(m_CurrentKey,Name.c_str(),NULL,NULL,(unsigned char *)tempbuf,&errorcode) != ERROR_SUCCESS )
    {
        return(ERROR_SYSTEM(::GetLastError()));
    }

	* Out = tempbuf;
    return(1);
}
//................................................................................................................................
int  MRegister::ReadString(MString Name,char * OutBuf,unsigned short InSize)
{
	register unsigned long					errorcode = InSize;

	if ( ::RegQueryValueEx(m_CurrentKey,Name.c_str(),NULL,NULL,(unsigned char *)OutBuf,&errorcode) != ERROR_SUCCESS )
    {
        return(ERROR_SYSTEM(::GetLastError()));
    }

    return(errorcode);
}
//................................................................................................................................
int  MRegister::WriteString(MString Name,MString In)
{
	if ( ::RegSetValueEx(m_CurrentKey,Name.c_str(),NULL,REG_SZ,(unsigned char *)In.c_str(),In.Length()) != ERROR_SUCCESS )
    {
        return(ERROR_SYSTEM(::GetLastError()));
    }

    return(1);
}
//................................................................................................................................
int  MRegister::ReadInteger(MString Name,unsigned long * Out)
{
	register unsigned long					errorcode = sizeof(unsigned long);

	if ( ::RegQueryValueEx(m_CurrentKey,Name.c_str(),NULL,NULL,(unsigned char *)Out,&errorcode) != ERROR_SUCCESS )
    {
        return(ERROR_SYSTEM(::GetLastError()));
    }

	return(1);
}
//................................................................................................................................
int  MRegister::WriteString(MString  Name,unsigned long In)
{
	if ( ::RegSetValueEx(m_CurrentKey,Name.c_str(),NULL,REG_DWORD,(unsigned char *)&In,sizeof(unsigned long)) != ERROR_SUCCESS )
    {
        return(ERROR_SYSTEM(::GetLastError()));
    }

    return(1);
}
//................................................................................................................................
int  MRegister::ReadBinary(MString Name,char * OutBuf,unsigned short InSize)
{
	register unsigned long					errorcode = InSize;

	if ( ::RegQueryValueEx(m_CurrentKey,Name.c_str(),NULL,NULL,(unsigned char *)OutBuf,&errorcode) != ERROR_SUCCESS )
    {
        return(ERROR_SYSTEM(::GetLastError()));
    }

    return(errorcode);
}
//................................................................................................................................
int  MRegister::WriteBinary(MString Name,char * InBuf,unsigned short InSize)
{
	if ( ::RegSetValueEx(m_CurrentKey,Name.c_str(),NULL,REG_BINARY,(unsigned char *)InBuf,InSize) != ERROR_SUCCESS )
    {
        return(ERROR_SYSTEM(::GetLastError()));
    }

    return(1);
}
//--------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------
