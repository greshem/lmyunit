//--------------------------------------------------------------------------------------------------------------------------------
#include "mdbffile.h"
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MMemoryDbfFile,MFile)

	ERROR_DEFINE(ERROR_MMEMORYDBFFILE_NOINSTANCE,"MMemoryDbfFile","操作发生错误[对象没有初始化]")
	ERROR_DEFINE(ERROR_MMEMORYDBFFILE_INVALIDFIELD,"MMemoryDbfFile","操作发生错误[无效的字段名称]")
	ERROR_DEFINE(ERROR_MMEMORYDBFFILE_DBFHEAD,"MMemoryDbfFile","打开文件发生错误[错误的DBF文件头部]")
	ERROR_DEFINE(ERROR_MMEMORYDBFFILE_NOMEMORY,"MMemoryDbfFile","打开文件发生错误[没有足够的内存可以分配]")
	ERROR_DEFINE(ERROR_MMEMORYDBFFILE_PARAM,"MMemoryDbfFile","操作发生错误[入口参数错误]")
	ERROR_DEFINE(ERROR_MMEMORYDBFFILE_NOFIND,"MMemoryDbfFile","操作发生错误[没有匹配的数据存在]")

END_LMYUNIT
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
		return(ERROR_MMEMORYDBFFILE_NOINSTANCE);
	}

	for ( i=0;i<=m_DbfFieldCount-1;i++ )
	{
		if ( strnicmp(FieldName,m_DbfField[i].FieldName,11) == 0 )
		{
			return(i);
		}
	}

	return(ERROR_MMEMORYDBFFILE_INVALIDFIELD);
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
		//不需要写入文件
		return(1);
	}

	m_EditFlag = false;
	if ( (errorcode = MFile::Open(m_FileName,MFILE_OPENMODE_WRITE | MFILE_OPENMODE_SHAREALL)) < 0 )
	{
		//不能打开文件进行写入
		return(errorcode);
	}

	//写入数据头部
	MFile::Seek(0,0);
	m_DbfHead.DataAddr = sizeof(tagDbfHead) + sizeof(unsigned char) + m_DbfFieldCount * sizeof(tagDbfField);
	MFile::Write((char *)&m_DbfHead,sizeof(tagDbfHead));

	//写入数据字段信息
	MFile::Write((char *)m_DbfField,sizeof(tagDbfField) * m_DbfFieldCount);

	//写入纪录开始标志
	MFile::Write(&startmarket,sizeof(unsigned char));

	//写入数据纪录
	record = m_DbfRecord;
	for ( i=0;i<=(int)m_DbfHead.RecordCount-1;i++ )
	{
		MFile::Write(record->RecordData,m_DbfHead.RecordSize);
		record = record->Next;
	}

	//写入数据纪录结束标记
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
		//不能打开文件
		return(errorcode);
	}

	strncpy(m_FileName,FileName.c_str(),256);

	MFile::Seek(0,0);
	if ( MFile::Read((char *)&m_DbfHead,sizeof(tagDbfHead)) != sizeof(tagDbfHead) )
	{
		//读取DBF头部信息错误
		MFile::Close();
		return(ERROR_MMEMORYDBFFILE_DBFHEAD);
	}

	m_DbfFieldCount = (m_DbfHead.DataAddr - sizeof(tagDbfHead)) / sizeof(tagDbfField);
	if ( m_DbfFieldCount <= 0 )
	{
		//读取DBF字段信息错误
		MFile::Close();
		return(ERROR_MMEMORYDBFFILE_DBFHEAD);
	}

	m_DbfField = new tagDbfField[m_DbfFieldCount];
	if ( m_DbfField == NULL )
	{
		//没有足够的内存可以分配
		MFile::Close();
		return(ERROR_MMEMORYDBFFILE_NOMEMORY);
	}

	if ( MFile::Read((char *)m_DbfField,sizeof(tagDbfField) * m_DbfFieldCount) != (int)(sizeof(tagDbfField) * m_DbfFieldCount) )
	{
		//读取DBF字段错误
		MFile::Close();
		return(ERROR_MMEMORYDBFFILE_DBFHEAD);
	}

	m_DbfField[0].FieldOffset = 1;
	for ( i=1;i<=m_DbfFieldCount-1;i++ )
	{
		m_DbfField[i].FieldOffset = m_DbfField[i-1].FieldOffset + m_DbfField[i-1].FieldSize;
	}
/*
	for( i=0; i<m_DbfFieldCount; i++)
	{
		//printf( "strncpy(records[%d].FieldName, \"%s\",10);\r\n", i,m_DbfField[i].FieldName );
		//printf( "records[%d].FieldType = \'%c\';\r\n", i,m_DbfField[i].FieldType );
		//printf( "records[%d].FieldOffset = %d;\r\n", i,m_DbfField[i].FieldOffset );
		//printf( "records[%d].FieldSize = %d;\r\n", i,m_DbfField[i].FieldSize );
		//printf( "records[%d].DecSize = %d;\r\n", i,m_DbfField[i].DecSize );
		//printf("\r\n");
		
		//printf( "{\"%s\",\t\'%c\',\t0,\t%d,\t%d},\r\n",m_DbfField[i].FieldName, m_DbfField[i].FieldType,
		//								     m_DbfField[i].FieldSize,m_DbfField[i].DecSize);
	}
*/

	//读取DBF纪录
	MFile::Seek(m_DbfHead.DataAddr,0);
	for ( i=0;i<=(int)m_DbfHead.RecordCount-1;i++ )
	{
		record = new tagDbfRecord;
		if ( record == NULL )
		{
			//没有足够的内存可以分配
			MFile::Close();
			return(ERROR_MMEMORYDBFFILE_NOMEMORY);
		}

		record->RecordData = new char[m_DbfHead.RecordSize];
		if ( record->RecordData == NULL )
		{
			//没有足够的内存可以分配
			MFile::Close();
			return(ERROR_MMEMORYDBFFILE_NOMEMORY);
		}

		if ( MFile::Read(record->RecordData,m_DbfHead.RecordSize) != m_DbfHead.RecordSize )
		{
			//不能读取纪录数据
			MFile::Close();
			return(ERROR_MMEMORYDBFFILE_DBFHEAD);
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
		for ( i=0;i<=(int)m_DbfHead.RecordCount-1;i++ )
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
	{//创建文件失败
		return (errorcode);
	}
	strncpy( m_FileName, szFileName, 255 );
	
	//初始化头
	unsigned long lToday = MDateTime::Now().DateToLong();
	memset( &m_DbfHead, 0, sizeof(tagDbfHead) );
	m_DbfHead.Market		= 0x03;
	m_DbfHead.UpdateYear	= (unsigned char)( lToday/10000 -1900 );
	m_DbfHead.UpdateMonth   = (unsigned char)( (lToday%10000)/100 );
	m_DbfHead.UpdateDay		= (unsigned char)( lToday%100 );
	m_DbfHead.RecordSize	= iRecordSize;
	
	//初始化列格式
	m_DbfFieldCount = iFieldCnt;
	m_DbfField = new tagDbfField[iFieldCnt];
	if ( m_DbfField == NULL )
	{//没有足够的内存可以分配
		MFile::Close();
		return(ERROR_MMEMORYDBFFILE_NOMEMORY);
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
		return(ERROR_MMEMORYDBFFILE_NOINSTANCE);
	}

	m_CurRecordPtr = m_DbfRecord;
	return(1);
}
//..............................................................................................................................
int  MMemoryDbfFile::Last(void)
{
	if ( m_CurRecordPtr == NULL || m_DbfRecord == NULL )
	{
		return(ERROR_MMEMORYDBFFILE_NOINSTANCE);
	}

	m_CurRecordPtr = m_DbfRecord->Front;
	return(1);
}
//..............................................................................................................................
int  MMemoryDbfFile::Prior(void)
{
	if ( m_CurRecordPtr == NULL || m_DbfRecord == NULL )
	{
		return(ERROR_MMEMORYDBFFILE_NOINSTANCE);
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
		return(ERROR_MMEMORYDBFFILE_NOINSTANCE);
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
		//没有调用Open函数
		return(ERROR_MMEMORYDBFFILE_NOINSTANCE);
	}

	if ( FieldNo >= m_DbfFieldCount )
	{
		//字段号错误
		return(ERROR_MMEMORYDBFFILE_INVALIDFIELD);
	}

	if ( InSize < m_DbfField[FieldNo].FieldSize )
	{
		//缓冲大小错误
		return(ERROR_MMEMORYDBFFILE_PARAM);
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
		//没有调用Open函数
		return(ERROR_MMEMORYDBFFILE_NOINSTANCE);
	}

	if ( FieldNo >= m_DbfFieldCount )
	{
		//字段号错误
		return(ERROR_MMEMORYDBFFILE_INVALIDFIELD);
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
		//没有调用Open函数
		return(ERROR_MMEMORYDBFFILE_NOINSTANCE);
	}

	record = new tagDbfRecord;
	if ( record == NULL )
	{
		return(ERROR_MMEMORYDBFFILE_NOMEMORY);
	}

	record->RecordData = new char[m_DbfHead.RecordSize];
	if ( record->RecordData == NULL )
	{
		delete record;
		return(ERROR_MMEMORYDBFFILE_NOMEMORY);
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
		//没有调用Open函数
		return(ERROR_MMEMORYDBFFILE_NOINSTANCE);
	}

	record = new tagDbfRecord;
	if ( record == NULL )
	{
		return(ERROR_MMEMORYDBFFILE_NOMEMORY);
	}

	record->RecordData = new char[m_DbfHead.RecordSize];
	if ( record->RecordData == NULL )
	{
		delete record;
		return(ERROR_MMEMORYDBFFILE_NOMEMORY);
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
		//没有调用Open函数
		return(ERROR_MMEMORYDBFFILE_NOINSTANCE);
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
		//没有调用Open函数
		return(ERROR_MMEMORYDBFFILE_NOINSTANCE);
	}

	if ( FieldNo >= m_DbfFieldCount )
	{
		return(ERROR_MMEMORYDBFFILE_INVALIDFIELD);
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

	return(ERROR_MMEMORYDBFFILE_NOFIND);
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
	//return((int)m_CurRecordPtr);
	return((long long )m_CurRecordPtr);
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
