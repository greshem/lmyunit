//--------------------------------------------------------------------------------------------------------------------------------
//                  ;;;,
//        ,;;;;;: ,;;;:.,;..
//         :;;"`,;;;;;;"":;;					��Ԫ���ƣ�INI�ļ���д����
//      ..;;:  .;;,.;;:',;;"
//    ,;;;;;;" :;`',;",;;"						��д���ڣ�2004��5��20
//   :" ,;:` , `:.;;;;;'
//    ,;;;,;:;;,;;;, ,;							��д��Ա��richtech
//   :;;;"` `:;;;;;,;,.;.
//   '""   .;;`.;";:;;;;` ;,					��ע��Ϣ��
//       .;"`  ::. '   .,;;;
//      ""     ';;;;;;;;;;`
//--------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMIniFileH__
#define __LmyUnitMIniFileH__
//--------------------------------------------------------------------------------------------------------------------------------
//����ͷ�ļ�
#include "mfile.h"
//................................................................................................................................
#ifdef WINDOWSCODE
//................................................................................................................................
//Windows����ϵͳ
//................................................................................................................................
#else
//................................................................................................................................
//Linux����ϵͳ
#include "stdlib.h"
//................................................................................................................................
#endif
//--------------------------------------------------------------------------------------------------------------------------------
#pragma pack(1)
//--------------------------------------------------------------------------------------------------------------------------------
typedef struct __INIFILEVALUE
{
	char						Name[256];
	char						Value[256];
	struct __INIFILEVALUE	*	Next;
	char						Content[512];
	unsigned short				ContentSize;
} tagIniFileValue;
//................................................................................................................................
typedef struct __INIFILESECTION
{
	char						SectionName[256];
	tagIniFileValue			*	ChildPtr;
	struct __INIFILESECTION *	Next;
	char						Content[512];
	unsigned short				ContentSize;
} tagIniFileSection;
//--------------------------------------------------------------------------------------------------------------------------------
#pragma pack()
//--------------------------------------------------------------------------------------------------------------------------------
#define		ERROR_MINIFILE_INVALIDSTATUS	(ERROR_USER(70))	//����INI�ļ���������[��Ч���ڲ�״̬]
#define		ERROR_MINIFILE_NOMEMORY			(ERROR_USER(71))	//����INI�ļ���������[û���㹻���ڴ���Է���]
#define		ERROR_MINIFILE_FILELENGTH		(ERROR_USER(72))	//����INI�ļ���������[�ļ�����С�ڵ���0]
//................................................................................................................................
class MIniFile : public MFile
{
protected:
	tagIniFileSection			m_Root;
	unsigned char				m_Status;
	unsigned long				m_PreEndOffset;
	unsigned char				m_PreEndType;
protected:
	char						m_Section[256];
	unsigned short				m_SectionCount;
	char						m_Name[256];
	unsigned short				m_NameCount;
	char						m_Value[256];
	unsigned short				m_ValueCount;
protected:
	tagIniFileSection		*	m_CurSection;
	tagIniFileValue			*	m_CurName;
protected:
	bool						m_EditFlag;
	char						m_FileName[256];
public:
	MIniFile(void);
	virtual ~MIniFile();
protected:
	__inline int  PutChar(unsigned char Value,char * InBuf,unsigned long No);
	__inline void Clear(void);
	__inline void Init(void);
	__inline tagIniFileSection * FindSection(char * Section,tagIniFileSection ** LastSectionPtr);
	__inline int  AddSection(void);
	__inline tagIniFileValue * FindName(char * Name,tagIniFileValue ** LastNamePtr);
	__inline int  AddName(void);
	__inline int  AddValue(void);
	__inline int  AddOther(void);
	__inline void EndofAnsys(char * InBuf,unsigned long No);
	__inline void SiftString(char * InString);
	__inline void WriteToFile(void);
public:
	int  Open(MString FileName);				
	int  Open(char * InBuf,unsigned long InSize);
	int  Create(MString FileName);
	void Close(void);
public:
	MString ReadString(MString Section,MString Name,MString Default);
	int	 ReadInteger(MString Section,MString Name,int Default);
	float ReadFloat(MString Section,MString Name,float Default);
	bool ReadBool(MString Section,MString Name,bool Default);
public:
	int  WriteString(MString Section,MString Name,MString Value);
	int  WriteInteger(MString Section,MString Name,int Value);
	int  WriteFloat(MString Section,MString Name,float Value);
	int  WriteBool(MString Section,MString Name,bool Value);
public:
	int  GetSectionCount(void);
	MString GetSectionName(unsigned short Serial);

	DECLARE_LMYUNIT(MIniFile)
};
//--------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------
