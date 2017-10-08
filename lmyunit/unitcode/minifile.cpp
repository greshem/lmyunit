//--------------------------------------------------------------------------------------------------------------------------------
#include "minifile.h"
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MIniFile,MFile)

	ERROR_DEFINE(ERROR_MINIFILE_INVALIDSTATUS,"MIniFile","解析INI文件发生错误[无效的内部状态]")
	ERROR_DEFINE(ERROR_MINIFILE_NOMEMORY,"MIniFile","解析INI文件发生错误[没有足够的内存可以分配]")
	ERROR_DEFINE(ERROR_MINIFILE_FILELENGTH,"MIniFile","解析INI文件发生错误[文件长度小于等于0]")
END_LMYUNIT
//..............................................................................................................................
MIniFile::MIniFile(void)
{
	Init();
}
//..............................................................................................................................
MIniFile::~MIniFile()
{
	Close();
}
//..............................................................................................................................
void MIniFile::SiftString(char * InString)
{
	register int							i;
	
	for ( i=strlen(InString)-1;i>=0;i-- )
	{
		if ( InString[i] == ' ' || InString[i] == 0x09 )
		{
			InString[i] = 0;
		}
		else
		{
			break;
		}
	}
}
//..............................................................................................................................
int  MIniFile::PutChar(unsigned char Value,char * InBuf,unsigned long No)
{
	register int					errorcode;

	if ( m_Status == 0 )
	{
		if ( Value == '[' )
		{
			//加入注释行
			if ( No > m_PreEndOffset )
			{
				if ( m_PreEndType == 0x00 )
				{
					//Section注释
					m_CurSection->ContentSize = (unsigned short)(No - m_PreEndOffset);
					if ( m_CurSection->ContentSize > 512 )
					{
						m_CurSection->ContentSize = 512;
					}

					memcpy(m_CurSection->Content,&InBuf[m_PreEndOffset],m_CurSection->ContentSize);
				}
				else
				{
					//Value注释
					m_CurName->ContentSize = (unsigned short)(No - m_PreEndOffset);
					if ( m_CurName->ContentSize > 512 )
					{
						m_CurName->ContentSize = 512;
					}
					memcpy(m_CurName->Content,&InBuf[m_PreEndOffset],m_CurName->ContentSize);
				}
			}

			m_SectionCount = 0;
			m_Status = 1;
		}
		else if ( Value == ';' )
		{
			m_Status = 5;
		}
		else if ( Value == 0x0D )
		{
			m_Status = 2;
		}
		else if ( Value != ' ' && Value != 0x09 && Value != 0x0A )
		{
			//加入注释行
			if ( No > m_PreEndOffset )
			{
				if ( m_PreEndType == 0x00 )
				{
					//Section注释
					m_CurSection->ContentSize = (unsigned short)(No - m_PreEndOffset);
					if ( m_CurSection->ContentSize > 512 )
					{
						m_CurSection->ContentSize = 512;
					}

					memcpy(m_CurSection->Content,&InBuf[m_PreEndOffset],m_CurSection->ContentSize);
				}
				else
				{
					//Value注释
					m_CurName->ContentSize = (unsigned short)(No - m_PreEndOffset);
					if ( m_CurName->ContentSize > 512 )
					{
						m_CurName->ContentSize = 512;
					}
					memcpy(m_CurName->Content,&InBuf[m_PreEndOffset],m_CurName->ContentSize);
				}
			}

			m_Name[0] = Value;
			m_NameCount = 1;
			m_Status = 3;
		}

		return(1);
	}
	else if ( m_Status == 1 )
	{
		if ( Value == 0x0D )
		{
			m_Status = 2;
		}
		else if ( Value == 0x0A )
		{
			m_Status = 0;
		}
		else if ( Value == ']' )
		{			
			m_PreEndOffset = No + 1;
			m_PreEndType = 0x00;

			//加入新的Section
			if ( (errorcode = AddSection()) < 0 )
			{
				return(errorcode);
			}

			m_Status = 0;
		}
		else
		{
			if ( m_SectionCount == 0 && (Value == ' ' || Value == 0x09) )
			{
				//过滤开始的空格和Tab
			}
			else if ( m_SectionCount < 255 )
			{
				m_Section[m_SectionCount] = Value;
				m_SectionCount ++;
			}
			else
			{
				//超过256个字符，丢弃
			}
		}

		return(1);
	}
	else if ( m_Status == 2 )
	{
		if ( Value == 0x0A )
		{
			m_Status = 0;
		}
		else
		{
			//0x0D后0x0A前的字符丢弃
		}

		return(1);
	}
	else if ( m_Status == 3 )
	{
		if ( Value == 0x0D )
		{
			m_Status = 2;
		}
		else if ( Value == 0x0A )
		{
			m_Status = 0;
		}
		else if ( Value == '=' )
		{
			//加入新的Name
			if ( (errorcode = AddName()) < 0 )
			{
				return(errorcode);
			}

			m_ValueCount = 0;
			m_Status = 4;
		}
		else
		{
			if ( m_NameCount == 0 && (Value == ' ' || Value == 0x09) )
			{
				//过滤开始的空格
			}
			else if ( m_NameCount < 255 )
			{
				m_Name[m_NameCount] = Value;
				m_NameCount ++;
			}
			else
			{
				//超过256个字符，丢弃
			}
		}

		return(1);
	}
	else if ( m_Status == 4 )
	{
		if ( Value == 0x0A || Value == 0x0D || Value == ';' || Value == 0x09 )
		{
			//加入新的Value
			if ( (errorcode = AddValue()) < 0 )
			{
				return(errorcode);
			}

			if ( Value == 0x0D )
			{
				m_Status = 2;
			}
			else if ( Value == 0x0A || Value == 0x09 )
			{
				m_Status = 0;
			}
			else
			{
				m_Status = 5;
			}

			m_PreEndOffset = No;
			m_PreEndType = 0x01;
		}
		else 
		{
			if ( m_ValueCount == 0 && (Value == ' ' || Value == 0x09) )
			{
				//过滤开始的空格
			}
			else if ( m_ValueCount < 255 )
			{
				m_Value[m_ValueCount] = Value;
				m_ValueCount ++;
			}
			else
			{
				//超过256个字符，丢弃
			}
		}

		return(1);
	}
	else if ( m_Status == 5 )
	{
		if ( Value == 0x0D )
		{
			m_Status = 2;
		}
		else if ( Value == 0x0A )
		{
			m_Status = 0;
		}

		return(1);
	}
	else
	{
		return(ERROR_MINIFILE_INVALIDSTATUS);
	}
}
//..............................................................................................................................
void MIniFile::Clear(void)
{
	tagIniFileSection							*	sectionptr;
	tagIniFileSection							*	deletesectionptr;
	tagIniFileValue								*	valueptr;
	tagIniFileValue								*	deletevalueptr;

	sectionptr = &m_Root;
	while ( sectionptr != NULL )
	{
		valueptr = sectionptr->ChildPtr;
		while ( valueptr != NULL )
		{
			deletevalueptr = valueptr;
			valueptr = valueptr->Next;

			delete deletevalueptr;
		}
		
		deletesectionptr = sectionptr;
		sectionptr = sectionptr->Next;

		if ( deletesectionptr != &m_Root )
		{
			delete deletesectionptr;
		}
	}
	m_Root.Next = NULL;
	m_Root.ChildPtr = NULL;
	m_Root.ContentSize = 0;
}
//..............................................................................................................................
void MIniFile::Init(void)
{
	m_Root.Next = NULL;
	m_Root.SectionName[0] = 0;
	m_Root.ChildPtr = NULL;
	m_Root.ContentSize = 0;

	m_Status = 0;
	m_PreEndOffset = 0;
	m_PreEndType = 0x00;
	
	memset(m_Section,0,256);
	m_SectionCount = 0;

	memset(m_Name,0,256);
	m_NameCount = 0;

	memset(m_Value,0,256);
	m_ValueCount = 0;

	m_CurSection = &m_Root;
	m_CurName = NULL;

	m_EditFlag = false;
	memset(m_FileName,0,256);
}
//..............................................................................................................................
tagIniFileSection * MIniFile::FindSection(char * Section,tagIniFileSection ** LastSectionPtr)
{
	tagIniFileSection						*	sectionptr;

	sectionptr = &m_Root;

	while ( sectionptr != NULL )
	{
		if ( strnicmp(Section,sectionptr->SectionName,256) == 0 )
		{
			return(sectionptr);
		}
		
		* LastSectionPtr = sectionptr;
		sectionptr = sectionptr->Next;
	}

	return(NULL);
}
//..............................................................................................................................
int  MIniFile::AddSection(void)
{
	tagIniFileSection						*	sectionptr;
	tagIniFileSection						*	lastsectionptr;

	m_Section[m_SectionCount] = 0;
	SiftString(m_Section);

	sectionptr = FindSection(m_Section,&lastsectionptr);
	if ( sectionptr == NULL )
	{
		sectionptr = new tagIniFileSection;
		if ( sectionptr == NULL )
		{
			return(ERROR_MINIFILE_NOMEMORY);
		}

		m_CurSection = sectionptr;

		strncpy(m_CurSection->SectionName,m_Section,256);
		m_CurSection->ChildPtr = NULL;
		m_CurSection->Next = NULL;
		m_CurSection->ContentSize = 0;

		lastsectionptr->Next = m_CurSection;
	}
	else
	{
		m_CurSection = sectionptr;
	}

	return(1);
}
//..............................................................................................................................
tagIniFileValue * MIniFile::FindName(char * Name,tagIniFileValue ** LastNamePtr)
{
	tagIniFileValue						*	valueptr;

	valueptr = m_CurSection->ChildPtr;
	* LastNamePtr = NULL;

	while ( valueptr != NULL )
	{
		if ( strnicmp(Name,valueptr->Name,256) == 0 )
		{
			return(valueptr);
		}

		* LastNamePtr = valueptr;
		valueptr = valueptr->Next;
	}

	return(NULL);
}
//..............................................................................................................................
int  MIniFile::AddName(void)
{
	tagIniFileValue						*	valueptr;
	tagIniFileValue						*	lastvalueptr;

	m_Name[m_NameCount] = 0;
	SiftString(m_Name);

	valueptr = FindName(m_Name,&lastvalueptr);
	if ( valueptr == NULL )
	{
		valueptr = new tagIniFileValue;
		if ( valueptr == NULL )
		{
			return(ERROR_MINIFILE_NOMEMORY);
		}
		m_CurName = valueptr;

		m_CurName->Next = NULL;
		strncpy(m_CurName->Name,m_Name,256);
		m_CurName->Value[0] = 0;
		m_CurName->ContentSize = 0;

		if ( lastvalueptr == NULL )
		{
			m_CurSection->ChildPtr = m_CurName;
		}
		else
		{
			lastvalueptr->Next = m_CurName;
		}
	}
	else
	{
		m_CurName = valueptr;
	}

	return(1);
}
//..............................................................................................................................
int  MIniFile::AddValue(void)
{
	if ( m_CurName == NULL )
	{
		return(ERROR_MINIFILE_INVALIDSTATUS);
	}

	m_Value[m_ValueCount] = 0;
	SiftString(m_Value);

	strncpy(m_CurName->Value,m_Value,256);

	return(1);
}
//..............................................................................................................................
void MIniFile::WriteToFile(void)
{
	tagIniFileSection						*	sectionptr;
	tagIniFileValue							*	valueptr;
	char										tempbuf[256];

	if ( m_EditFlag == false || m_FileName[0] == 0 )
	{
		//没有修改或内存INI文件不必写入到磁盘
		return;
	}

	if ( MFile::Open(m_FileName,MFILE_OPENMODE_WRITE | MFILE_OPENMODE_SHAREALL) < 0 )
	{
		if ( MFile::Create(m_FileName) < 0 )
		{
			//不能写入文件
			return;
		}
	}

	MFile::Seek(0,0);

	sectionptr = &m_Root;

	while ( sectionptr != NULL )
	{
		if ( sectionptr != &m_Root )
		{
			//不是默认的Section，写入Section
			_snprintf(tempbuf,256,"[%s]",sectionptr->SectionName);
			MFile::Write(tempbuf,strlen(tempbuf));
		}

		//写入注释行
		if ( sectionptr->ContentSize > 0 )
		{
			MFile::Write(sectionptr->Content,sectionptr->ContentSize);
		}

		valueptr = sectionptr->ChildPtr;
		while ( valueptr != NULL )
		{
			_snprintf(tempbuf,256,"%s = %s",valueptr->Name,valueptr->Value);
			MFile::Write(tempbuf,strlen(tempbuf));

			//写入注释行
			if ( valueptr->ContentSize > 0 )
			{
				MFile::Write(valueptr->Content,valueptr->ContentSize);
			}

			valueptr = valueptr->Next;
		}

		sectionptr = sectionptr->Next;
	}

	m_EditFlag = false;

	MFile::SetFileLength();
	MFile::Close();
}
//..............................................................................................................................
void MIniFile::EndofAnsys(char * InBuf,unsigned long No)
{
	PutChar(0x0D,InBuf,No);
	PutChar(0x0A,InBuf,No);
	PutChar('[',InBuf,No);
}
//..............................................................................................................................
int  MIniFile::Open(MString FileName)
{
	char								*	tempbuf = NULL;
	int										filelength;
	register int							errorcode;
	char									defaultbuf[8192];

	if ( (errorcode = MFile::Open(FileName)) < 0 )
	{
		return(errorcode);
	}

	filelength = MFile::Seek(0,2);
	if ( filelength < 0 )
	{
		MFile::Close();
		return(ERROR_MINIFILE_FILELENGTH);
	}
	else if ( filelength == 0 )
	{
		MFile::Close();

		Init();
		strncpy(m_FileName,FileName.c_str(),256);
		return(1);
	}

	if ( filelength > 8192 )
	{
		tempbuf = new char[filelength];
		if ( tempbuf == NULL )
		{
			MFile::Close();
			return(ERROR_MINIFILE_NOMEMORY);
		}
	}
	else
	{
		tempbuf = (char *)defaultbuf;
	}

	memset(tempbuf,0,filelength);

	MFile::Seek(0,0);
	if ( (errorcode = MFile::Read(tempbuf,filelength)) != filelength )
	{
		if ( tempbuf != defaultbuf )
		{
			delete [] tempbuf;
		}

		MFile::Close();
		return(errorcode);
	}

	MFile::Close();

	if ( (errorcode = Open(tempbuf,filelength)) < 0 )
	{
		if ( tempbuf != defaultbuf )
		{
			delete [] tempbuf;
		}

		return(errorcode);
	}
	else
	{
		if ( tempbuf != defaultbuf )
		{
			delete [] tempbuf;
		}

		strncpy(m_FileName,FileName.c_str(),256);
		return(1);
	}
}
//..............................................................................................................................
int  MIniFile::Open(char * InBuf,unsigned long InSize)
{
	register unsigned long					i;
	register int							errorcode;

	Init();

	for ( i=0;i<=InSize-1;i++ )
	{
		if ( (errorcode = PutChar((unsigned char)InBuf[i],InBuf,i)) < 0 )
		{
			return(errorcode);
		}
	}

	EndofAnsys(InBuf,InSize);

	return(1);
}
//..............................................................................................................................
int  MIniFile::Create(MString FileName)
{
	Init();
	strncpy(m_FileName,FileName.c_str(),256);

	return(1);
}
//..............................................................................................................................
void MIniFile::Close(void)
{
	WriteToFile();
	Clear();
}
//..............................................................................................................................
MString MIniFile::ReadString(MString Section,MString Name,MString Default)
{
	tagIniFileSection							*	sectionptr;
	tagIniFileSection							*	lastsectionptr;
	tagIniFileValue								*	nameptr;
	tagIniFileValue								*	lastnameptr;

	sectionptr = FindSection(Section.c_str(),&lastsectionptr);
	if ( sectionptr == NULL )
	{
		return(Default);
	}

	m_CurSection = sectionptr;
	nameptr = FindName(Name.c_str(),&lastnameptr);
	if ( nameptr == NULL )
	{
		return(Default);
	}
	else
	{
		return(nameptr->Value);
	}
}
//..............................................................................................................................
int	 MIniFile::ReadInteger(MString Section,MString Name,int Default)
{
	int								value;
	char						*	stopptr;
	char							tempbuf[256];

	_snprintf(tempbuf,256,"%d",Default);
	value = strtol(ReadString(Section,Name,tempbuf).c_str(),&stopptr,10);
	return(value);
}
//..............................................................................................................................
float MIniFile::ReadFloat(MString Section,MString Name,float Default)
{
	float							value;
	char						*	stopptr;
	char							tempbuf[256];

	_snprintf(tempbuf,256,"%f",Default);
	value = (float)strtod(ReadString(Section,Name,tempbuf).c_str(),&stopptr);
	return(value);
}
//..............................................................................................................................
bool MIniFile::ReadBool(MString Section,MString Name,bool Default)
{
	if ( Default == false )
	{
		if ( ReadString(Section,Name,"false") == "false" )
		{
			return(false);
		}
		else
		{
			return(true);
		}
	}
	else
	{
		if ( ReadString(Section,Name,"true") == "false" )
		{
			return(false);
		}
		else
		{
			return(true);
		}
	}
}
//..............................................................................................................................
int  MIniFile::WriteString(MString Section,MString Name,MString Value)
{
	tagIniFileSection							*	sectionptr;
	tagIniFileSection							*	lastsectionptr;
	tagIniFileValue								*	nameptr;
	tagIniFileValue								*	lastnameptr;

	sectionptr = FindSection(Section.c_str(),&lastsectionptr);
	if ( sectionptr == NULL )
	{
		sectionptr = new tagIniFileSection;
		if ( sectionptr == NULL )
		{
			return(ERROR_MINIFILE_NOMEMORY);
		}

		strncpy(sectionptr->SectionName,Section.c_str(),256);
		sectionptr->ChildPtr = NULL;
		sectionptr->Next = NULL;
		sprintf(sectionptr->Content,"\r\n");
		sectionptr->ContentSize = 2;

		lastsectionptr->Next = sectionptr;
	}

	m_EditFlag = true;
	m_CurSection = sectionptr;

	nameptr = FindName(Name.c_str(),&lastnameptr);
	if ( nameptr == NULL )
	{
		nameptr = new tagIniFileValue;
		if ( nameptr == NULL )
		{
			return(ERROR_MINIFILE_NOMEMORY);
		}

		strncpy(nameptr->Name,Name.c_str(),256);
		strncpy(nameptr->Value,Value.c_str(),256);
		strncpy(nameptr->Content,"\r\n",256);
		nameptr->ContentSize = 2;
		nameptr->Next = NULL;

		if ( lastnameptr != NULL )
		{
			lastnameptr->Next = nameptr;
		}
		else
		{
			m_CurSection->ChildPtr = nameptr;
		}

		return(1);
	}
	else
	{
		strncpy(nameptr->Value,Value.c_str(),256);
		return(1);
	}
}
//..............................................................................................................................
int  MIniFile::WriteInteger(MString Section,MString Name,int Value)
{
	char								tempbuf[256];

	_snprintf(tempbuf,256,"%d",Value);
	return(WriteString(Section,Name,tempbuf));
}
//..............................................................................................................................
int  MIniFile::WriteFloat(MString Section,MString Name,float Value)
{
	char								tempbuf[256];

	_snprintf(tempbuf,256,"%f",Value);
	return(WriteString(Section,Name,tempbuf));
}
//..............................................................................................................................
int  MIniFile::WriteBool(MString Section,MString Name,bool Value)
{
	if ( Value == true )
	{
		return(WriteString(Section,Name,"true"));
	}
	else
	{
		return(WriteString(Section,Name,"false"));
	}
}
//..............................................................................................................................
int  MIniFile::GetSectionCount(void)
{
	tagIniFileSection						*	sectionptr;
	register int								errorcode = 0;
	
	sectionptr = &m_Root;
	while ( sectionptr != NULL )
	{
		errorcode ++;
		sectionptr = sectionptr->Next;
	}
	
	return(errorcode - 1);
}
//..............................................................................................................................
MString MIniFile::GetSectionName(unsigned short Serial)
{
	tagIniFileSection						*	sectionptr;
	register int								errorcode = 0;

	sectionptr = &m_Root;
	while ( sectionptr != NULL )
	{
		if ( (errorcode - 1) == Serial )
		{
			return(sectionptr->SectionName);
		}

		errorcode ++;
		sectionptr = sectionptr->Next;
	}

	return("");
}
//--------------------------------------------------------------------------------------------------------------------------------
