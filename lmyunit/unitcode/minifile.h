//--------------------------------------------------------------------------------------------------------------------------------
//                  ;;;,
//        ,;;;;;: ,;;;:.,;..
//         :;;"`,;;;;;;"":;;					单元名称：INI文件读写处理
//      ..;;:  .;;,.;;:',;;"
//    ,;;;;;;" :;`',;",;;"						编写日期：2004年5月20
//   :" ,;:` , `:.;;;;;'
//    ,;;;,;:;;,;;;, ,;							编写人员：richtech
//   :;;;"` `:;;;;;,;,.;.
//   '""   .;;`.;";:;;;;` ;,					备注信息：
//       .;"`  ::. '   .,;;;
//      ""     ';;;;;;;;;;`
//--------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMIniFileH__
#define __LmyUnitMIniFileH__
//--------------------------------------------------------------------------------------------------------------------------------
//公共头文件
#include "mfile.h"
//................................................................................................................................
#ifdef WINDOWSCODE
//................................................................................................................................
//Windows操作系统
//................................................................................................................................
#else
//................................................................................................................................
//Linux操作系统
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
#define		ERROR_MINIFILE_INVALIDSTATUS	(ERROR_USER(70))	//解析INI文件发生错误[无效的内部状态]
#define		ERROR_MINIFILE_NOMEMORY			(ERROR_USER(71))	//解析INI文件发生错误[没有足够的内存可以分配]
#define		ERROR_MINIFILE_FILELENGTH		(ERROR_USER(72))	//解析INI文件发生错误[文件长度小于等于0]
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
