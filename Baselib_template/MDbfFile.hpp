//--------------------------------------------------------------------------------------------------------------------------------
//                  ;;;,
//        ,;;;;;: ,;;;:.,;..
//         :;;"`,;;;;;;"":;;					��Ԫ���ƣ�DBF�ļ���д����
//      ..;;:  .;;,.;;:',;;"
//    ,;;;;;;" :;`',;",;;"						��д���ڣ�2004��5��20
//   :" ,;:` , `:.;;;;;'
//    ,;;;,;:;;,;;;, ,;							��д��Ա��qianzj
//   :;;;"` `:;;;;;,;,.;.
//   '""   .;;`.;";:;;;;` ;,					��ע��Ϣ��
//       .;"`  ::. '   .,;;;
//      ""     ';;;;;;;;;;`
//--------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMDbfFileH__
#define __LmyUnitMDbfFileH__
//--------------------------------------------------------------------------------------------------------------------------------
//����ͷ�ļ�
#include "MFile.hpp"
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

//	DECLARE_LMYUNIT(MMemoryDbfFile)
};
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//#include "MDbfFile.h"
//--------------------------------------------------------------------------------------------------------------------------------
//BEGIN_LMYUNIT(MMemoryDbfFile,MFile)

//	ERROR_DEFINE(ERROR_MMEMORYDBFFILE_NOINSTANCE,"MMemoryDbfFile","������������[����û�г�ʼ��]")

//	ERROR_DEFINE(ERROR_MMEMORYDBFFILE_INVALIDFIELD,"MMemoryDbfFile","������������[��Ч���ֶ�����]")

//	ERROR_DEFINE(ERROR_MMEMORYDBFFILE_DBFHEAD,"MMemoryDbfFile","���ļ���������[�����DBF�ļ�ͷ��]")
		
		
////	ERROR_DEFINE(ERROR_MMEMORYDBFFILE_NOMEMORY,"MMemoryDbfFile","���ļ���������[û���㹻���ڴ���Է���]")
	
	
////	ERROR_DEFINE(ERROR_MMEMORYDBFFILE_PARAM,"MMemoryDbfFile","������������[��ڲ�������]")
	
//	ERROR_DEFINE(ERROR_MMEMORYDBFFILE_NOFIND,"MMemoryDbfFile","������������[û��ƥ������ݴ���]")

////END_LMYUNIT
//..............................................................................................................................
MMemoryDbfFile::MMemoryDbfFile(void)
{
	m_DbfField = NULL;
	m_DbfFieldCount = 0;
	m_DbfRecord = NULL;
	m_CurRecordPtr = NULL;
	m_EditFlag = false;
	memset(m_FileName,0,256);
}
//..............................................................................................................................
MMemoryDbfFile::~MMemoryDbfFile()
{
	Close();
}
//..............................................................................................................................
void MMemoryDbfFile::SiftBlank(char * InBuf,unsigned short InSize)
{
	register int							i;

	for ( i=InSize-1;i>=0;i-- )
	{
		if ( (unsigned char)InBuf[i] == 0x20 )
		{
			InBuf[i] = 0;
		}
		else
		{
			break;
		}
	}
}
//..............................................................................................................................
int  MMemoryDbfFile::FindFieldName(char * FieldName)
{
	register int								i;

	if ( m_DbfField == NULL )
	{
//		return(ERROR_MMEMORYDBFFILE_NOINSTANCE);
		return -1;
	}

	for ( i=0;i<=m_DbfFieldCount-1;i++ )
	{
		if ( strnicmp(FieldName,m_DbfField[i].FieldName,11) == 0 )
		{
			return(i);
		}
	}

//	return(ERROR_MMEMORYDBFFILE_INVALIDFIELD);
	return -1;
	
}
//..............................................................................................................................
int  MMemoryDbfFile::WriteToFile(void)
{
	register int								i;
	tagDbfRecord							*	record;
	char										startmarket = 0x0D;
	char										endmarket = 0x1A;
	register int								errorcode;

	if ( m_EditFlag == false || m_DbfField == NULL || m_DbfRecord == NULL )
	{
		//����Ҫд���ļ�
		return(1);
	}

	m_EditFlag = false;
	if ( (errorcode = MFile::Open(m_FileName,MFILE_OPENMODE_WRITE | MFILE_OPENMODE_SHAREALL)) < 0 )
	{
		//���ܴ��ļ�����д��
		return(errorcode);
	}

	//д������ͷ��
	MFile::Seek(0,0);
	m_DbfHead.DataAddr = sizeof(tagDbfHead) + sizeof(unsigned char) + m_DbfFieldCount * sizeof(tagDbfField);
	MFile::Write((char *)&m_DbfHead,sizeof(tagDbfHead));

	//д�������ֶ���Ϣ
	MFile::Write((char *)m_DbfField,sizeof(tagDbfField) * m_DbfFieldCount);

	//д���¼��ʼ��־
	MFile::Write(&startmarket,sizeof(unsigned char));

	//д�����ݼ�¼
	record = m_DbfRecord;
	for ( i=0;i<=(int)m_DbfHead.RecordCount-1;i++ )
	{
		MFile::Write(record->RecordData,m_DbfHead.RecordSize);
		record = record->Next;
	}

	//д�����ݼ�¼�������
	MFile::Write(&endmarket,sizeof(unsigned char));

	MFile::Close();
	return(1);
}
//..............................................................................................................................
int  MMemoryDbfFile::Open(MString FileName)
{
	register int						i;
	tagDbfRecord					*	record;
	register int						errorcode;

	Close();
	if ( (errorcode = MFile::Open(FileName)) < 0 )
	{
		//���ܴ��ļ�
		return(errorcode);
	}

	strncpy(m_FileName,FileName.c_str(),256);

	MFile::Seek(0,0);
	if ( MFile::Read((char *)&m_DbfHead,sizeof(tagDbfHead)) != sizeof(tagDbfHead) )
	{
		//��ȡDBFͷ����Ϣ����
		MFile::Close();
//		return(ERROR_MMEMORYDBFFILE_DBFHEAD);
		return -1;
	}

	m_DbfFieldCount = (m_DbfHead.DataAddr - sizeof(tagDbfHead)) / sizeof(tagDbfField);
	if ( m_DbfFieldCount <= 0 )
	{
		//��ȡDBF�ֶ���Ϣ����
		MFile::Close();
//		return(ERROR_MMEMORYDBFFILE_DBFHEAD);
		return -1;
	}

	m_DbfField = new tagDbfField[m_DbfFieldCount];
	if ( m_DbfField == NULL )
	{
		//û���㹻���ڴ���Է���
		MFile::Close();
//		return(ERROR_MMEMORYDBFFILE_NOMEMORY);
				return -1;
	}

	if ( MFile::Read((char *)m_DbfField,sizeof(tagDbfField) * m_DbfFieldCount) != (int)(sizeof(tagDbfField) * m_DbfFieldCount) )
	{
		//��ȡDBF�ֶδ���
		MFile::Close();
//		return(ERROR_MMEMORYDBFFILE_DBFHEAD);
				return -1;
	}

	m_DbfField[0].FieldOffset = 1;
	for ( i=1;i<=m_DbfFieldCount-1;i++ )
	{
		m_DbfField[i].FieldOffset = m_DbfField[i-1].FieldOffset + m_DbfField[i-1].FieldSize;
	}

	for( i=0; i<m_DbfFieldCount; i++)
	{
		printf( "strncpy(records[%d].FieldName, \"%s\",10);\r\n", i,m_DbfField[i].FieldName );
		printf( "records[%d].FieldType = \'%c\';\r\n", i,m_DbfField[i].FieldType );
		printf( "records[%d].FieldOffset = %ld;\r\n", i,m_DbfField[i].FieldOffset );
		printf( "records[%d].FieldSize = %d;\r\n", i,m_DbfField[i].FieldSize );
		printf( "records[%d].DecSize = %d;\r\n", i,m_DbfField[i].DecSize );
		printf("\r\n");
		
		//printf( "{\"%s\",\t\'%c\',\t0,\t%d,\t%d},\r\n",m_DbfField[i].FieldName, m_DbfField[i].FieldType,
		//								     m_DbfField[i].FieldSize,m_DbfField[i].DecSize);
	}

	unsigned int nDbfRecord = 0;
	MFile::Seek( 0, 0 );
	nDbfRecord = (MFile::GetFileLength() -  m_DbfHead.DataAddr)/m_DbfHead.RecordSize;
	if ( nDbfRecord != m_DbfHead.RecordCount )
	{
		//�ļ����ȴ���
		MFile::Close();
//		return(ERROR_MMEMORYDBFFILE_DBFHEAD);	
				return -1;
	}
	//��ȡDBF��¼
	MFile::Seek(m_DbfHead.DataAddr,0);
	for ( i=0;i<=(int)m_DbfHead.RecordCount-1;i++ )
	{
		record = new tagDbfRecord;
		if ( record == NULL )
		{
			//û���㹻���ڴ���Է���
			MFile::Close();
		//	return(ERROR_MMEMORYDBFFILE_NOMEMORY);
					return -1;
		}

		record->RecordData = new char[m_DbfHead.RecordSize];
		if ( record->RecordData == NULL )
		{
			//û���㹻���ڴ���Է���
			MFile::Close();
		//	return(ERROR_MMEMORYDBFFILE_NOMEMORY);
					return -1;
		}

		if ( MFile::Read(record->RecordData,m_DbfHead.RecordSize) != m_DbfHead.RecordSize )
		{
			//���ܶ�ȡ��¼����
			MFile::Close();
		//	return(ERROR_MMEMORYDBFFILE_DBFHEAD);
					return -1;
		}

		if ( m_DbfRecord == NULL || m_CurRecordPtr == NULL )
		{
			record->Front = record;
			record->Next = record;
			m_DbfRecord = record;
			m_CurRecordPtr = record;
		}
		else
		{
			record->Front = m_CurRecordPtr;
			record->Next = m_DbfRecord;

			m_CurRecordPtr->Next = record;
			m_DbfRecord->Front = record;

			m_CurRecordPtr = record;
		}
	}

	m_CurRecordPtr = m_DbfRecord;
	MFile::Close();
	return(1);
}
//..............................................................................................................................
void MMemoryDbfFile::Close(void)
{
	register int							i;
	tagDbfRecord						*	record;
	tagDbfRecord						*	tempptr;

	WriteToFile();

	if ( m_DbfField != NULL )
	{
		delete [] m_DbfField;
		m_DbfField = NULL;
	}
	m_DbfFieldCount = 0;

	if ( m_DbfRecord != NULL )
	{
		record = m_DbfRecord;
		for ( i=0; record && i<=(int)m_DbfHead.RecordCount-1;i++ )
		{
			if ( record->RecordData != NULL )
			{
				delete [] record->RecordData;
				record->RecordData = NULL;
			}

			tempptr = record;
			record = record->Next;

			delete tempptr;
		}
		m_DbfRecord = NULL;
	}
	m_CurRecordPtr = NULL;
	m_DbfHead.RecordCount = 0;
}
//..............................................................................................................................
int  MMemoryDbfFile::Flush(void)
{
	return(WriteToFile());
}
//........................................................................
int	 MMemoryDbfFile::Create( const char* szFileName, unsigned short iRecordSize, 
							 const tagDbfField* pDbfField, int iFieldCnt )
{
	int		errorcode;

	Close();
	if( (errorcode = MFile::Create( szFileName)) <0 )
	{//�����ļ�ʧ��
		return (errorcode);
	}
	strncpy( m_FileName, szFileName, 255 );
	
	//��ʼ��ͷ
	unsigned long lToday = MDateTime::Now().DateToLong();
	memset( &m_DbfHead, 0, sizeof(tagDbfHead) );
	m_DbfHead.Market		= 0x03;
	m_DbfHead.UpdateYear	= (unsigned char)( lToday/10000 -1900 );
	m_DbfHead.UpdateMonth   = (unsigned char)( (lToday%10000)/100 );
	m_DbfHead.UpdateDay		= (unsigned char)( lToday%100 );
	m_DbfHead.RecordSize	= iRecordSize;
	
	//��ʼ���и�ʽ
	m_DbfFieldCount = iFieldCnt;
	m_DbfField = new tagDbfField[iFieldCnt];
	if ( m_DbfField == NULL )
	{//û���㹻���ڴ���Է���
		MFile::Close();
//		return(ERROR_MMEMORYDBFFILE_NOMEMORY);
				return -1;
	}	
	memcpy( m_DbfField, pDbfField, sizeof(tagDbfField) * iFieldCnt );

	m_DbfField[0].FieldOffset = 1;
	for ( int i=1;i<m_DbfFieldCount;i++ )
		m_DbfField[i].FieldOffset = m_DbfField[i-1].FieldOffset + m_DbfField[i-1].FieldSize;
		
	m_EditFlag = true;
	return (1);
}
//..............................................................................................................................
int  MMemoryDbfFile::First(void)
{
	if ( m_CurRecordPtr == NULL || m_DbfRecord == NULL )
	{
	//	return(ERROR_MMEMORYDBFFILE_NOINSTANCE);
		return -1;
	}

	m_CurRecordPtr = m_DbfRecord;
	return(1);
}
//..............................................................................................................................
int  MMemoryDbfFile::Last(void)
{
	if ( m_CurRecordPtr == NULL || m_DbfRecord == NULL )
	{
//		return(ERROR_MMEMORYDBFFILE_NOINSTANCE);
				return -1;
	}

	m_CurRecordPtr = m_DbfRecord->Front;
	return(1);
}
//..............................................................................................................................
int  MMemoryDbfFile::Prior(void)
{
	if ( m_CurRecordPtr == NULL || m_DbfRecord == NULL )
	{
	//	return(ERROR_MMEMORYDBFFILE_NOINSTANCE);
				return -1;
	}

	if ( m_CurRecordPtr != m_DbfRecord )
	{
		m_CurRecordPtr = m_CurRecordPtr->Front;
		return(1);
	}
	else
	{
		return(0);
	}
}
//..............................................................................................................................
int  MMemoryDbfFile::Next(void)
{
	if ( m_CurRecordPtr == NULL || m_DbfRecord == NULL )
	{
	//	return(ERROR_MMEMORYDBFFILE_NOINSTANCE);
				return -1;
	}

	if ( m_CurRecordPtr != m_DbfRecord->Front )
	{
		m_CurRecordPtr = m_CurRecordPtr->Next;
		return(1);
	}
	else
	{
		return(0);
	}
}
//..............................................................................................................................
int  MMemoryDbfFile::ReadString(unsigned short FieldNo,char * Value,unsigned short InSize)
{
	if ( m_CurRecordPtr == NULL || m_DbfRecord == NULL || m_DbfField == NULL )
	{
		//û�е���Open����
	//	return(ERROR_MMEMORYDBFFILE_NOINSTANCE);
				return -1;
	}

	if ( FieldNo >= m_DbfFieldCount )
	{
		//�ֶκŴ���
	//	return(ERROR_MMEMORYDBFFILE_INVALIDFIELD);
				return -1;
	}

	if ( InSize < m_DbfField[FieldNo].FieldSize )
	{
		//�����С����
	//	return(ERROR_MMEMORYDBFFILE_PARAM);
				return -1;
	}

	memset( Value, 0, InSize );
	memcpy(Value,m_CurRecordPtr->RecordData + m_DbfField[FieldNo].FieldOffset,m_DbfField[FieldNo].FieldSize);
	SiftBlank(Value,m_DbfField[FieldNo].FieldSize);

	return(m_DbfField[FieldNo].FieldSize);
}
//..............................................................................................................................
int  MMemoryDbfFile::ReadString(char * FieldName,char * Value,unsigned short InSize)
{
	int											no;

	if ( (no = FindFieldName(FieldName)) < 0 )
	{
		return(no);
	}

	return(ReadString(no,Value,InSize));
}
//..............................................................................................................................
int  MMemoryDbfFile::WriteString(unsigned short FieldNo,char * Value)
{
	int											errorcode = 0;

	if ( m_CurRecordPtr == NULL || m_DbfRecord == NULL || m_DbfField == NULL )
	{
		//û�е���Open����
//		return(ERROR_MMEMORYDBFFILE_NOINSTANCE);
				return -1;
	}

	if ( FieldNo >= m_DbfFieldCount )
	{
		//�ֶκŴ���
	//	return(ERROR_MMEMORYDBFFILE_INVALIDFIELD);
				return -1;
	}

	errorcode = strlen(Value);
	if ( errorcode > m_DbfField[FieldNo].FieldSize )
	{
		errorcode = m_DbfField[FieldNo].FieldSize;
	}

	memset(m_CurRecordPtr->RecordData + m_DbfField[FieldNo].FieldOffset,0x20,m_DbfField[FieldNo].FieldSize);
	memcpy(m_CurRecordPtr->RecordData + m_DbfField[FieldNo].FieldOffset,Value,errorcode);

	m_EditFlag = true;

	return(1);
}
//..............................................................................................................................
int  MMemoryDbfFile::WriteString(char * FieldName,char * Value)
{
	int											no;

	if ( (no = FindFieldName(FieldName)) < 0 )
	{
		return(no);
	}

	return(WriteString(no,Value));
}
//..............................................................................................................................
int  MMemoryDbfFile::ReadInteger(unsigned short FieldNo,int * Value)
{
	char										tempbuf[256];
	char									*	stringptr;
	register int								errorcode;

	if ( (errorcode = ReadString(FieldNo,tempbuf,256)) < 0 )
	{
		return(errorcode);
	}
	
	* Value = strtol(tempbuf,&stringptr,10);
	return(1);
}
//..............................................................................................................................
int  MMemoryDbfFile::ReadInteger(char * FieldName,int * Value)
{
	char										tempbuf[256];
	char									*	stringptr;
	register int								errorcode;

	if ( (errorcode = ReadString(FieldName,tempbuf,256)) < 0 )
	{
		return(errorcode);
	}

	* Value = strtol(tempbuf,&stringptr,10);
	return(1);
}
//..............................................................................................................................
int  MMemoryDbfFile::WriteInteger(unsigned short FieldNo,int Value)
{
	char										tempbuf[256];

	_snprintf(tempbuf,256,"%d",Value);
	return(WriteString(FieldNo,tempbuf));
}
//..............................................................................................................................
int  MMemoryDbfFile::WriteInteger(char * FieldName,int Value)
{
	char										tempbuf[256];

	_snprintf(tempbuf,256,"%d",Value);
	return(WriteString(FieldName,tempbuf));
}
//..............................................................................................................................
int  MMemoryDbfFile::ReadFloat(unsigned short FieldNo,float * Value)
{
	char										tempbuf[256];
	char									*	stringptr;
	register int								errorcode;

	if ( (errorcode = ReadString(FieldNo,tempbuf,256)) < 0 )
	{
		return(errorcode);
	}

	* Value = (float)strtod(tempbuf,&stringptr);
	return(1);
}
//..............................................................................................................................
int  MMemoryDbfFile::ReadFloat(char * FieldName,float * Value)
{
	char										tempbuf[256];
	char									*	stringptr;
	register int								errorcode;

	if ( (errorcode = ReadString(FieldName,tempbuf,256)) < 0 )
	{
		return(errorcode);
	}

	* Value = (float)strtod(tempbuf,&stringptr);
	return(1);
}
//..............................................................................................................................
int  MMemoryDbfFile::WriteFloat(unsigned short FieldNo,float Value)
{
	char										tempbuf[256];

	_snprintf(tempbuf,256,"%f",Value);
	return(WriteString(FieldNo,tempbuf));
}
//..............................................................................................................................
int  MMemoryDbfFile::WriteFloat(char * FieldName,float Value)
{
	char										tempbuf[256];

	_snprintf(tempbuf,256,"%f",Value);
	return(WriteString(FieldName,tempbuf));
}
//..............................................................................................................................
int  MMemoryDbfFile::AppendRecord(void)
{
	tagDbfRecord							*	record;

	if ( m_DbfField == NULL )
	{
		//û�е���Open����
//		return(ERROR_MMEMORYDBFFILE_NOINSTANCE);
				return -1;
	}

	record = new tagDbfRecord;
	if ( record == NULL )
	{
	//	return(ERROR_MMEMORYDBFFILE_NOMEMORY);
				return -1;
	}

	record->RecordData = new char[m_DbfHead.RecordSize];
	if ( record->RecordData == NULL )
	{
		delete record;
	//	return(ERROR_MMEMORYDBFFILE_NOMEMORY);
				return -1;
	}
	memset(record->RecordData,0x20,m_DbfHead.RecordSize);

	if ( m_DbfRecord == NULL || m_CurRecordPtr == NULL )
	{
		record->Front = record;
		record->Next = record;
		m_DbfRecord = record;
		m_CurRecordPtr = record;
	}
	else
	{
		record->Front = m_CurRecordPtr;
		record->Next = m_DbfRecord;

		m_CurRecordPtr->Next = record;
		m_DbfRecord->Front = record;

		m_CurRecordPtr = record;
	}

	m_DbfHead.RecordCount ++;
	m_EditFlag = true;
	return(1);
}
//..............................................................................................................................
int	 MMemoryDbfFile::InsertRecord(void)
{
	tagDbfRecord							*	record;

	if ( m_DbfField == NULL )
	{
		//û�е���Open����
	//	return(ERROR_MMEMORYDBFFILE_NOINSTANCE);
				return -1;
	}

	record = new tagDbfRecord;
	if ( record == NULL )
	{
		//return(ERROR_MMEMORYDBFFILE_NOMEMORY);
				return -1;
	}

	record->RecordData = new char[m_DbfHead.RecordSize];
	if ( record->RecordData == NULL )
	{
		delete record;
	//	return(ERROR_MMEMORYDBFFILE_NOMEMORY);
				return -1;
	}
	memset(record->RecordData,0x20,m_DbfHead.RecordSize);

	if ( m_DbfRecord == NULL || m_CurRecordPtr == NULL )
	{
		record->Front = record;
		record->Next = record;
		m_DbfRecord = record;
		m_CurRecordPtr = record;
	}
	else
	{
		record->Next = m_CurRecordPtr;
		record->Front = m_CurRecordPtr->Front;

		m_CurRecordPtr->Front->Next = record;
		m_CurRecordPtr->Front = record;

		if ( m_CurRecordPtr == m_DbfRecord )
		{
			m_DbfRecord = record;
		}
		m_CurRecordPtr = record;
	}

	m_DbfHead.RecordCount ++;
	m_EditFlag = true;
	return(1);
}
//..............................................................................................................................
int  MMemoryDbfFile::DelRecord(void)
{
	if ( m_CurRecordPtr == NULL || m_DbfRecord == NULL || m_DbfField == NULL )
	{
		//û�е���Open����
		//return(ERROR_MMEMORYDBFFILE_NOINSTANCE);
				return -1;
	}

	m_CurRecordPtr->RecordData[0] = 0x2A;
	m_EditFlag = true;
	return(1);
}
//..............................................................................................................................
int  MMemoryDbfFile::FindRecord(unsigned short FieldNo,char * Value)
{
	register int								i;
	char										tempbuf[256];

	if ( m_CurRecordPtr == NULL || m_DbfRecord == NULL || m_DbfField == NULL )
	{
		//û�е���Open����
	//	return(ERROR_MMEMORYDBFFILE_NOINSTANCE);
				return -1;
	}

	if ( FieldNo >= m_DbfFieldCount )
	{
	//	return(ERROR_MMEMORYDBFFILE_INVALIDFIELD);
				return -1;
	}

	memset(tempbuf,0x20,256);
	memcpy(tempbuf,Value,strlen(Value));

	for ( i=0;i<=(int)m_DbfHead.RecordCount-1;i++ )
	{
		if ( memcmp(m_CurRecordPtr->RecordData + m_DbfField[FieldNo].FieldOffset,tempbuf,m_DbfField[FieldNo].FieldSize) == 0 )
		{
			return(1);
		}

		m_CurRecordPtr = m_CurRecordPtr->Next;
	}

//	return(ERROR_MMEMORYDBFFILE_NOFIND);
			return -1;
}
//..............................................................................................................................
int  MMemoryDbfFile::FindRecord(char * FieldName,char * Value)
{
	int												no;

	if ( (no = FindFieldName(FieldName)) < 0 )
	{
		return(no);
	}

	return(FindRecord(no,Value));
}
//..............................................................................................................................
int  MMemoryDbfFile::GetCurRecord(void)
{
	return(reinterpret_cast<int>( m_CurRecordPtr));
}
//..............................................................................................................................
int  MMemoryDbfFile::SetCurRecord(int CurPtr)
{
	m_CurRecordPtr = (tagDbfRecord *)CurPtr;
	return(1);
}
//..............................................................................................................................
bool MMemoryDbfFile::IsDel(void)
{
	if ( m_CurRecordPtr == NULL )
	{
		return(true);
	}

	if ( (unsigned char)m_CurRecordPtr->RecordData[0] == 0x2A )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
#endif