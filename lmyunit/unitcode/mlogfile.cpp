//--------------------------------------------------------------------------------------------------------------------------------
#include "mlogfile.h"
#include "msysteminfo.h"
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MLogFile,MFile)

	ERROR_DEFINE(ERROR_MLOGFILE_FILEHEAD,"MLogFile","打开文件发生错误[错误的文件头部]")

END_LMYUNIT
//................................................................................................................................
MLogFile::MLogFile(void)
{

}
//................................................................................................................................
MLogFile::~MLogFile()
{
	Release();
}
//................................................................................................................................
int  MLogFile::Instance(MString FileName,unsigned short MaxRecord)
{
	register int						errorcode;

	if ( (errorcode = m_RecordData.Instance(MLOGFILE_MEMORY_SIZE)) < 0 )
	{
		return(errorcode);
	}

	if ( MFile::Open(FileName,MFILE_OPENMODE_READWRITE | MFILE_OPENMODE_SHAREALL) > 0 )
	{
		if ( MFile::Read((char *)&m_LogFileHead,sizeof(tagLogFileHeadInfo)) != sizeof(tagLogFileHeadInfo) )
		{
			MFile::Close();

			return(ERROR_MLOGFILE_FILEHEAD);
		}

		if ( strncmp(m_LogFileHead.MarketFlag,"MLOG日志文件",20) != 0 )
		{
			MFile::Close();

			return(ERROR_MLOGFILE_FILEHEAD);
		}

		if ( strtod(m_LogFileHead.Version,NULL) * 100 != 100 )
		{
			MFile::Close();

			return(ERROR_MLOGFILE_FILEHEAD);
		}

		m_LogFileMaxRecord = (unsigned short)strtol(m_LogFileHead.MaxRecord,NULL,10);
		m_LogFileFirst = (unsigned short)strtol(m_LogFileHead.First,NULL,10);
		m_LogFileLast = (unsigned short)strtol(m_LogFileHead.Last,NULL,10);

		return(1);
	}
	else if ( (errorcode = MFile::Create(FileName)) > 0 )
	{
		memset((char *)&m_LogFileHead,0x20,sizeof(tagLogFileHeadInfo));

		strncpy(m_LogFileHead.MarketFlag,"MLOG日志文件",20);
		strncpy(m_LogFileHead.VersionMarket,"版本：",20);
		strncpy(m_LogFileHead.Version,"1.00",10);
		strncpy(m_LogFileHead.MaxRecordMarket,"最大纪录数量：",20);
		_snprintf(m_LogFileHead.MaxRecord,10,"%d",MaxRecord);
		strncpy(m_LogFileHead.FirstMarket,"起始位置：",20);
		strncpy(m_LogFileHead.First,"0",10);
		strncpy(m_LogFileHead.LastMarket,"结束位置：",20);
		strncpy(m_LogFileHead.Last,"0",10);
		strncpy(m_LogFileHead.InfoFlagMarket,"信息纪录：",20);
		m_LogFileHead.InfoFlag = 'Y';
		strncpy(m_LogFileHead.WarningFlagMarket,"警告纪录：",20);
		m_LogFileHead.WarningFlag = 'Y';
		strncpy(m_LogFileHead.ErrorFlagMarket,"错误纪录：",20);
		m_LogFileHead.ErrorFlag = 'Y';
		strncpy(m_LogFileHead.LogSucFlagMarket,"成功审核：",20);
		m_LogFileHead.LogSucFlag = 'Y';
		strncpy(m_LogFileHead.LogFalFlagMarket,"失败审核：",20);
		m_LogFileHead.LogFalFlag = 'Y';
		memset(m_LogFileHead.Reserved,0x20,9);
		strncpy(m_LogFileHead.Return,"\r\n",2);

		m_LogFileMaxRecord = MaxRecord;
		m_LogFileFirst = 0;
		m_LogFileLast = 0;

		if ( (errorcode = MFile::Write((char *)&m_LogFileHead,sizeof(tagLogFileHeadInfo))) != sizeof(tagLogFileHeadInfo) )
		{
			MFile::Close();

			return(errorcode);
		}

		return(1);
	}
	else
	{
		return(errorcode);
	}
}
//................................................................................................................................
void MLogFile::Release(void)
{
	MFile::Close();
}
//................................................................................................................................
void MLogFile::WriteReport(unsigned char Type,char * Source,char * Content,unsigned short InSize)
{
	char										tempbuf[256];
	tagLogFileMemoryInfo					*	tempinfo;
	tagLogFileRecordInfo						filerecord;

	tempinfo = (tagLogFileMemoryInfo *)tempbuf;
	tempinfo->LogType = Type;
	tempinfo->DateTime.SetCurDateTime();
	strncpy(tempinfo->Source,Source,20);
	if ( InSize > (255 - sizeof(tagLogFileMemoryInfo)) )
	{
		tempinfo->ContentSize = 255 - sizeof(tagLogFileMemoryInfo);
	}
	else
	{
		tempinfo->ContentSize = InSize;
	}
	memcpy(tempbuf + sizeof(tagLogFileMemoryInfo),Content,tempinfo->ContentSize);
	tempbuf[255] = 0;
	m_RecordData.PutData(tempbuf,tempinfo->ContentSize + sizeof(tagLogFileMemoryInfo));

	m_Section.Lock();

	if (	(Type == MLOGTYPE_INFO && m_LogFileHead.InfoFlag == 'Y' ) ||
			(Type == MLOGTYPE_WARNING && m_LogFileHead.WarningFlag == 'Y' ) ||
			(Type == MLOGTYPE_ERROR && m_LogFileHead.ErrorFlag == 'Y' ) ||
			(Type == MLOGTYPE_LOGSUC && m_LogFileHead.LogSucFlag == 'Y' ) ||
			(Type == MLOGTYPE_LOGFAL && m_LogFileHead.LogFalFlag == 'Y' ) )
	{
		memset((char *)&filerecord,0x20,sizeof(tagLogFileRecordInfo));

		if ( Type == MLOGTYPE_INFO )
		{
			_snprintf(filerecord.LogType,10,"[信息]",10);
		}
		else if ( Type == MLOGTYPE_WARNING )
		{
			_snprintf(filerecord.LogType,10,"[警告]",10);
		}
		else if ( Type == MLOGTYPE_ERROR )
		{
			_snprintf(filerecord.LogType,10,"[错误]",10);
		}
		else if ( Type == MLOGTYPE_LOGSUC )
		{
			_snprintf(filerecord.LogType,10,"[审核成功]",10);
		}
		else if ( Type == MLOGTYPE_LOGFAL )
		{
			_snprintf(filerecord.LogType,10,"[审核失败]",10);
		}
		_snprintf(filerecord.DateTime,21,"(%s)",tempinfo->DateTime.DateTimeToString().c_str());
		_snprintf(filerecord.RecordContent,200,"[%s]%s",Source,Content);
		filerecord.ReturnFlag[0] = 0x0D;
		filerecord.ReturnFlag[1] = 0x0A;
		

		MFile::Seek(sizeof(tagLogFileHeadInfo) + m_LogFileLast * sizeof(tagLogFileRecordInfo),0);
		MFile::Write((char *)&filerecord,sizeof(tagLogFileRecordInfo));

		m_LogFileLast = (m_LogFileLast + 1) % m_LogFileMaxRecord;
		if ( m_LogFileLast == m_LogFileFirst )
		{
			m_LogFileFirst = (m_LogFileLast + 1) % m_LogFileMaxRecord;
		}

		_snprintf(m_LogFileHead.First,10,"%d",m_LogFileFirst);
		_snprintf(m_LogFileHead.Last,10,"%d",m_LogFileLast);

		MFile::Seek(0,0);
		MFile::Write((char *)&m_LogFileHead,sizeof(tagLogFileHeadInfo));
	}

	m_Section.UnLock();
}
//................................................................................................................................
void MLogFile::WriteView(char * Source,const char * Format,...)
{
	char										tempbuf[256];
	va_list										marker;

	va_start(marker,Format);
	_vsnprintf(tempbuf,256,Format,marker);
	va_end( marker );

	WriteReport(MLOGTYPE_VIEW,Source,tempbuf,strlen(tempbuf) + 1);
}
//................................................................................................................................
void MLogFile::WriteInfo(char * Source,const char * Format,...)
{
	char										tempbuf[256];
	va_list										marker;

	va_start(marker,Format);
	_vsnprintf(tempbuf,256,Format,marker);
	va_end( marker );

	WriteReport(MLOGTYPE_INFO,Source,tempbuf,strlen(tempbuf) + 1);
}
//................................................................................................................................
void MLogFile::WriteWarning(char * Source,const char * Format,...)
{
	char										tempbuf[256];
	va_list										marker;

	va_start(marker,Format);
	_vsnprintf(tempbuf,256,Format,marker);
	va_end( marker );

	WriteReport(MLOGTYPE_WARNING,Source,tempbuf,strlen(tempbuf) + 1);
}
//................................................................................................................................
void MLogFile::WriteError(char * Source,const char * Format,...)
{
	char										tempbuf[256];
	va_list										marker;

	va_start(marker,Format);
	_vsnprintf(tempbuf,256,Format,marker);
	va_end( marker );

	WriteReport(MLOGTYPE_ERROR,Source,tempbuf,strlen(tempbuf) + 1);
}
//................................................................................................................................
void MLogFile::WriteLogSuc(char * Source,const char * Format,...)
{
	char										tempbuf[256];
	va_list										marker;

	va_start(marker,Format);
	_vsnprintf(tempbuf,256,Format,marker);
	va_end( marker );

	WriteReport(MLOGTYPE_LOGSUC,Source,tempbuf,strlen(tempbuf) + 1);
}
//................................................................................................................................
void MLogFile::WriteLogFal(char * Source,const char * Format,...)
{
	char										tempbuf[256];
	va_list										marker;

	va_start(marker,Format);
	_vsnprintf(tempbuf,256,Format,marker);
	va_end( marker );

	WriteReport(MLOGTYPE_LOGFAL,Source,tempbuf,strlen(tempbuf) + 1);
}
//................................................................................................................................
void MLogFile::WriteDebug(char * Source,char * Content,char * DebugInfo,unsigned short InSize)
{
	char										tempbuf[256];

	_snprintf(tempbuf,256,"%s[DEBUG： ",Content);
	if ( InSize > (250 - sizeof(tempbuf)) )
	{
		InSize = (unsigned short)(250 - sizeof(tempbuf));
	}
	memcpy(tempbuf + strlen(tempbuf),DebugInfo,InSize);
	memcpy(tempbuf + strlen(tempbuf) + InSize,"]",1);

	WriteReport(MLOGTYPE_ERROR,Source,tempbuf,strlen(tempbuf) + InSize + 1);
}
//................................................................................................................................
int  MLogFile::GetLogInfo(unsigned char * Type,MString * Source,MString * Content,MDateTime * DateTime)
{
	tagLogFileMemoryInfo						tempinfo;
	char										tempbuf[256];
	register int								errorcode;

	if ( (errorcode = m_RecordData.GetData((char *)&tempinfo,sizeof(tagLogFileMemoryInfo))) <= 0 )
	{
		return(errorcode);
	}

	* Type = tempinfo.LogType;
	* Source = tempinfo.Source;
	* DateTime = tempinfo.DateTime;

	if ( (errorcode = m_RecordData.GetData(tempbuf,tempinfo.ContentSize)) > 0 )
	{
		* Content = tempbuf;

		return(1);
	}

	return(errorcode);
}
//................................................................................................................................
void MLogFile::WriteAddtionLog(const char * Format,...)
{
	MFile										fileptr;
	MString										filepath;
	char										tempbuf[256];
	va_list										marker;

	filepath = MSystemInfo::GetApplicationFilePath() + "addtion.log";
	if ( fileptr.Open(filepath,MFILE_OPENMODE_WRITE | MFILE_OPENMODE_SHAREALL) < 0 )
	{
		if ( fileptr.Create(filepath) < 0 )
		{
			return;
		}
	}

	va_start(marker,Format);
	_vsnprintf(tempbuf,256,Format,marker);
	va_end( marker );

	fileptr.Seek(0,2);
	fileptr.Write(tempbuf,strlen(tempbuf));

	_snprintf(tempbuf,256,"%s\r\n",MDateTime::Now().DateTimeToString().c_str());

	fileptr.Write(tempbuf,strlen(tempbuf));

	fileptr.Close();
}
//--------------------------------------------------------------------------------------------------------------------------------
