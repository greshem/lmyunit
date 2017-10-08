//--------------------------------------------------------------------------------------------------------------------------------
//                  ;;;,
//        ,;;;;;: ,;;;:.,;..
//         :;;"`,;;;;;;"":;;					��Ԫ���ƣ�DBF�ļ���д����
//      ..;;:  .;;,.;;:',;;"
//    ,;;;;;;" :;`',;",;;"						��д���ڣ�2004��5��20
//   :" ,;:` , `:.;;;;;'
//    ,;;;,;:;;,;;;, ,;							��д��Ա��richtech
//   :;;;"` `:;;;;;,;,.;.
//   '""   .;;`.;";:;;;;` ;,					��ע��Ϣ��
//       .;"`  ::. '   .,;;;
//      ""     ';;;;;;;;;;`
//--------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMDbfFileH__
#define __LmyUnitMDbfFileH__
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
typedef struct
{
    char                    Market;         //���ݿ⿪ʼ��־
    unsigned char           UpdateYear;     //��������(��)
    unsigned char           UpdateMonth;    //��������(��)
    unsigned char           UpdateDay;      //��������(��)
    unsigned long           RecordCount;    //��¼��
    unsigned short          DataAddr;       //��������ʼλ��
    unsigned short          RecordSize;     //ÿ����¼����
    char                    Reserved[20];   //����
} tagDbfHead;
//................................................................................................................................
//DBF�ֶ�����
typedef struct
{
    char                    FieldName[11];  //�ֶ�����
    char                    FieldType;      //�ֶ����� C �ַ� N ���� L D ����
    unsigned long           FieldOffset;    //����ÿһ����¼��ƫ����
    unsigned char           FieldSize;      //�ֶγ���
    unsigned char           DecSize;        //С��λ��
    char                    Reserved[14];   //����      
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
#define			ERROR_MMEMORYDBFFILE_NOINSTANCE		(ERROR_USER(80))	//����MMemoryDbfFile��������[����û�г�ʼ��]
#define			ERROR_MMEMORYDBFFILE_INVALIDFIELD	(ERROR_USER(81))	//����MMemoryDbfFile��������[��Ч���ֶ�����]
#define			ERROR_MMEMORYDBFFILE_DBFHEAD		(ERROR_USER(82))	//��MMemoryDbfFile��������[�����DBF�ļ�ͷ��]
#define			ERROR_MMEMORYDBFFILE_NOMEMORY		(ERROR_USER(83))	//��MMemoryDbfFile��������[û���㹻���ڴ���Է���]
#define			ERROR_MMEMORYDBFFILE_PARAM			(ERROR_USER(84))	//����MMemoryDbfFile��������[��ڲ�������]
#define			ERROR_MMEMORYDBFFILE_NOFIND			(ERROR_USER(85))	//����MMemoryDbfFile��������[û��ƥ������ݴ���]
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
