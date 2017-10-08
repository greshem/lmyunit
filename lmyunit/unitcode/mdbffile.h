//--------------------------------------------------------------------------------------------------------------------------------
//                  ;;;,
//        ,;;;;;: ,;;;:.,;..
//         :;;"`,;;;;;;"":;;					单元名称：DBF文件读写处理
//      ..;;:  .;;,.;;:',;;"
//    ,;;;;;;" :;`',;",;;"						编写日期：2004年5月20
//   :" ,;:` , `:.;;;;;'
//    ,;;;,;:;;,;;;, ,;							编写人员：richtech
//   :;;;"` `:;;;;;,;,.;.
//   '""   .;;`.;";:;;;;` ;,					备注信息：
//       .;"`  ::. '   .,;;;
//      ""     ';;;;;;;;;;`
//--------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMDbfFileH__
#define __LmyUnitMDbfFileH__
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
typedef struct
{
    char                    Market;         //数据库开始标志
    unsigned char           UpdateYear;     //更新日期(年)
    unsigned char           UpdateMonth;    //更新日期(月)
    unsigned char           UpdateDay;      //更新日期(日)
    unsigned long           RecordCount;    //记录数
    unsigned short          DataAddr;       //数据区开始位置
    unsigned short          RecordSize;     //每条纪录长度
    char                    Reserved[20];   //保留
} tagDbfHead;
//................................................................................................................................
//DBF字段描述
typedef struct
{
    char                    FieldName[11];  //字段名称
    char                    FieldType;      //字段类型 C 字符 N 数字 L D 日期
    unsigned long           FieldOffset;    //对于每一条纪录的偏移量
    unsigned char           FieldSize;      //字段长度
    unsigned char           DecSize;        //小数位数
    char                    Reserved[14];   //保留      
} tagDbfField;
//................................................................................................................................
typedef struct __DBFRECORD
{
	char				*	RecordData;
	struct __DBFRECORD	*	Front;
	struct __DBFRECORD	*	Next;
} tagDbfRecord;
//--------------------------------------------------------------------------------------------------------------------------------
#pragma pack()
//--------------------------------------------------------------------------------------------------------------------------------
#define			ERROR_MMEMORYDBFFILE_NOINSTANCE		(ERROR_USER(80))	//操作MMemoryDbfFile发生错误[对象没有初始化]
#define			ERROR_MMEMORYDBFFILE_INVALIDFIELD	(ERROR_USER(81))	//操作MMemoryDbfFile发生错误[无效的字段名称]
#define			ERROR_MMEMORYDBFFILE_DBFHEAD		(ERROR_USER(82))	//打开MMemoryDbfFile发生错误[错误的DBF文件头部]
#define			ERROR_MMEMORYDBFFILE_NOMEMORY		(ERROR_USER(83))	//打开MMemoryDbfFile发生错误[没有足够的内存可以分配]
#define			ERROR_MMEMORYDBFFILE_PARAM			(ERROR_USER(84))	//操作MMemoryDbfFile发生错误[入口参数错误]
#define			ERROR_MMEMORYDBFFILE_NOFIND			(ERROR_USER(85))	//操作MMemoryDbfFile发生错误[没有匹配的数据存在]
//................................................................................................................................
class MMemoryDbfFile : public MFile
{
private:
	tagDbfHead				m_DbfHead;
	tagDbfField			*	m_DbfField;
	unsigned short			m_DbfFieldCount;
	tagDbfRecord		*	m_DbfRecord;
	tagDbfRecord		*	m_CurRecordPtr;
	bool					m_EditFlag;
	char					m_FileName[256];
private:
	__inline int  WriteToFile(void);
	__inline int  FindFieldName(char * FieldName);
	__inline void SiftBlank(char * InBuf,unsigned short InSize);
public:
	MMemoryDbfFile(void);
	~MMemoryDbfFile();
public:
	int  Open(MString FileName);
	void Close(void);
	int  Flush(void);
	int	 Create( const char* szFileName, unsigned short iRecordSize, const tagDbfField* pDbfField, int iFieldCnt );

public:
	int  First(void);
	int  Last(void);
	int  Prior(void);
	int  Next(void);
public:
	int  ReadString(unsigned short FieldNo,char * Value,unsigned short InSize);
	int  ReadString(char * FieldName,char * Value,unsigned short InSize);
	int  WriteString(unsigned short FieldNo,char * Value);
	int  WriteString(char * FieldName,char * Value);
public:
	int  ReadInteger(unsigned short FieldNo,int * Value);
	int  ReadInteger(char * FieldName,int * Value);
	int  WriteInteger(unsigned short FieldNo,int Value);
	int  WriteInteger(char * FieldName,int Value);
public:
	int  ReadFloat(unsigned short FieldNo,float * Value);
	int  ReadFloat(char * FieldName,float * Value);
	int  WriteFloat(unsigned short FieldNo,float Value);
	int  WriteFloat(char * FieldName,float Value);
public:
	int  AppendRecord(void);
	int	 InsertRecord(void);
	int  DelRecord(void);
public:
	int  FindRecord(unsigned short FieldNo,char * Value);
	int  FindRecord(char * FieldName,char * Value);
public:
	int  GetCurRecord(void);
	int  SetCurRecord(int CurPtr);
public:
	bool IsDel(void);

	DECLARE_LMYUNIT(MMemoryDbfFile)
};
//--------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------
