//#####################################################################################
//                  ;;;,
//        ,;;;;;: ,;;;:.,;..
//         :;;"`,;;;;;;"":;;					单元名称：日志文件读写处理
//      ..;;:  .;;,.;;:',;;"
//    ,;;;;;;" :;`',;",;;"						编写日期：2010年8月12 转换成stl
//   :" ,;:` , `:.;;;;;'
//    ,;;;,;:;;,;;;, ,;							编写人员：qianzj
//   :;;;"` `:;;;;;,;,.;.
//   '""   .;;`.;";:;;;;` ;,					备注信息：
//       .;"`  ::. '   .,;;;
//      ""     ';;;;;;;;;;`
//#####################################################################################
#ifndef __LmyUnitMLogFileH__
#define __LmyUnitMLogFileH__
//#####################################################################################
//公共头文件
#include "MFile.hpp"
//#include "MObject.h"
#include "MString.hpp"
#include "MDataStruct.hpp"
#include "MString.hpp"
#include "MMutex.hpp"
#include "MDateTime.hpp"
//#####################################################################################
#ifdef WINDOWSCODE
//#####################################################################################
//Windows操作系统
//#####################################################################################
#else
//#####################################################################################
//Linux操作系统
#include "stdlib.h"
//#####################################################################################
#endif
//#####################################################################################
#pragma pack(1)
//#####################################################################################
enum
{
	MLOGTYPE_VIEW = 0,									//流水日志
	MLOGTYPE_INFO,										//信息日志
	MLOGTYPE_WARNING,									//警告日志
	MLOGTYPE_ERROR,										//错误日志
	MLOGTYPE_LOGSUC,									//成功审核
	MLOGTYPE_LOGFAL,									//失败审核
};
//#####################################################################################
typedef struct
{
	char						MarketFlag[20];			//标志[MLOG日志文件]
	char						VersionMarket[20];		//版本描述[版本：]
	char						Version[10];			//版本
	char						MaxRecordMarket[20];	//最大纪录数：
	char						MaxRecord[10];			//最大纪录数
	char						FirstMarket[20];		//第一条纪录位置：
	char						First[10];				//第一条纪录
	char						LastMarket[20];			//最后一条纪录位置：
	char						Last[10];				//最后一条纪录
	char						InfoFlagMarket[20];		//允许信息纪录：
	char						InfoFlag;				//允许信息
	char						WarningFlagMarket[20];	//允许警告纪录：
	char						WarningFlag;			//允许警告
	char						ErrorFlagMarket[20];	//允许错误纪录：
	char						ErrorFlag;				//允许错误
	char						LogSucFlagMarket[20];	//允许审核成功纪录：
	char						LogSucFlag;				//允许审核成功
	char						LogFalFlagMarket[20];	//允许审核失败纪录：
	char						LogFalFlag;				//允许审核失败
	char						Reserved[9];			//保留
	char						Return[2];				//回车换行
} tagLogFileHeadInfo;
//#####################################################################################
typedef struct
{
	char						LogType[10];		//类型
	char						DateTime[21];		//记录时间，如(2004.03.28 15:30:20)
	char						RecordContent[200];	//记录内容
	char						ReturnFlag[2];		//回车换行标志
} tagLogFileRecordInfo;
//#####################################################################################
template <typename T> class  tagLogFileMemoryInfo
{
public:
	unsigned char				LogType;			//类型
	MDateTime<T>					DateTime;			//纪录时间
	char						Source[20];			//来源
	unsigned short				ContentSize;		//内容长度
} ;
//#####################################################################################
#pragma pack()
//#####################################################################################
#define		MLOGFILE_MEMORY_SIZE	10240				//内存日志缓冲
//#####################################################################################
#define		ERROR_MLOGFILE_FILEHEAD			(ERROR_USER(100))		//打开MLogFile发生错误[错误的文件头部]
//#####################################################################################
template <typename T> class MLogFile : public MFile<T>
{
protected:
	MCharLoopGroupMt<T>				m_RecordData;
protected:
	MCriticalSection<T>					m_Section;
	unsigned short						m_LogFileMaxRecord;
	unsigned short						m_LogFileFirst;
	unsigned short						m_LogFileLast;
public:
	tagLogFileHeadInfo					m_LogFileHead;
	void WriteReport(unsigned char Type,char * Source,char * Content,unsigned short InSize);
public:
	MLogFile(void);
	virtual ~MLogFile();
public:
	int  Instance(MString<T> FileName,unsigned short MaxRecord = 1000);
	void Release(void);
public:
	void WriteView(char * Source,const char * Format,...);
	void WriteInfo(char * Source,const char * Format,...);
	void WriteWarning(char * Source,const char * Format,...);
	void WriteError(char * Source,const char * Format,...);
	void WriteLogSuc(char * Source,const char * Format,...);
	void WriteLogFal(char * Source,const char * Format,...);
	void WriteDebug(char * Source,char * Content,char * DebugInfo,unsigned int  InSize);
	void WriteAddtionLog(const char * Format,...);
public:
	int  GetLogInfo(unsigned char * Type,MString<T> * Source,MString<T> * Content,MDateTime<T> * DateTime);

//	DECLARE_LMYUNIT(MLogFile)
};
//#####################################################################################
//#####################################################################################
//#####################################################################################
//#include "MLogFile.h"
//#include "MFile.cpp"
//#include "MString.h"
//#include "MDateTime.cpp"
//#include "MRegister.cpp"
//#include "MSystemInfo.cpp"
//#include "MMutex.cpp"
//#include "MDataStruct.cpp"
//#####################################################################################
//BEGIN_LMYUNIT(MLogFile,MFile)

//	ERROR_DEFINE(ERROR_MLOGFILE_FILEHEAD,"MLogFile","打开文件发生错误[错误的文件头部]")

//END_LMYUNIT
//#####################################################################################
template <typename T> MLogFile<T>::MLogFile(void)
{

}
//#####################################################################################
 template <typename T> MLogFile<T>::~MLogFile()
{
	Release();
}
//#####################################################################################
 template <typename T> int  MLogFile<T>::Instance(MString<T> FileName,unsigned short MaxRecord)
{
	register int						errorcode;

	if ( (errorcode = m_RecordData.Instance(MLOGFILE_MEMORY_SIZE)) < 0 )
	{
		return(errorcode);
	}

	if ( MFile<T>::Open(FileName,MFILE_OPENMODE_READWRITE | MFILE_OPENMODE_SHAREALL) > 0 )
	{
		if ( MFile<T>::Read((char *)&m_LogFileHead,sizeof(tagLogFileHeadInfo)) != sizeof(tagLogFileHeadInfo) )
		{
			MFile<T>::Close();

//			return(ERROR_MLOGFILE_FILEHEAD);
					return -1;
		}

		if ( strncmp(m_LogFileHead.MarketFlag,"MLOG日志文件",20) != 0 )
		{
			MFile<T>::Close();

//			return(ERROR_MLOGFILE_FILEHEAD);
					return -1;
		}

		if ( strtod(m_LogFileHead.Version,NULL) * 100 != 100 )
		{
			MFile<T>::Close();

//			return(ERROR_MLOGFILE_FILEHEAD);
					return -1;
		}

		m_LogFileMaxRecord = (unsigned short)strtol(m_LogFileHead.MaxRecord,NULL,10);
		m_LogFileFirst = (unsigned short)strtol(m_LogFileHead.First,NULL,10);
		m_LogFileLast = (unsigned short)strtol(m_LogFileHead.Last,NULL,10);

		return(1);
	}
	else if ( (errorcode = MFile<T>::Create(FileName)) > 0 )
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

		if ( (errorcode = MFile<T>::Write((char *)&m_LogFileHead,sizeof(tagLogFileHeadInfo))) != sizeof(tagLogFileHeadInfo) )
		{
			MFile<T>::Close();

			return(errorcode);
		}

		return(1);
	}
	else
	{
		return(errorcode);
	}
}
//#####################################################################################
 template <typename T> void MLogFile<T>::Release(void)
{
	MFile<T>::Close();
}
//#####################################################################################
 template <typename T> void MLogFile<T>::WriteReport(unsigned char Type,char * Source,char * Content,unsigned short InSize)
{
	char										tempbuf[256];
	tagLogFileMemoryInfo<T>					*	tempinfo;
	tagLogFileRecordInfo						filerecord;

	tempinfo = (tagLogFileMemoryInfo<T> *)tempbuf;
	tempinfo->LogType = Type;
	tempinfo->DateTime.SetCurDateTime();
	strncpy(tempinfo->Source,Source,20);
	if ( InSize > (255 - sizeof(tagLogFileMemoryInfo<T>)) )
	{
		tempinfo->ContentSize = 255 - sizeof(tagLogFileMemoryInfo<T>);
	}
	else
	{
		tempinfo->ContentSize = InSize;
	}
	memcpy(tempbuf + sizeof(tagLogFileMemoryInfo<T>),Content,tempinfo->ContentSize);
	tempbuf[255] = 0;
	m_RecordData.PutData(tempbuf,tempinfo->ContentSize + sizeof(tagLogFileMemoryInfo<T>));

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
#ifdef WINDOWSCODE
			_snprintf(filerecord.LogType,10,"[信息]",10);
#else
		snprintf(filerecord.LogType,10,"[信息]");
#endif
		
		}
		else if ( Type == MLOGTYPE_WARNING )
		{

#ifdef WINDOWSCODE
			_snprintf(filerecord.LogType,10,"[警告]",10);
#else
			snprintf(filerecord.LogType,10,"[警告]");
#endif
		}
		else if ( Type == MLOGTYPE_ERROR )
		{

#ifdef WINDOWSCODE
			_snprintf(filerecord.LogType,10,"[错误]",10);
#else
			snprintf(filerecord.LogType,10,"[错误]");
#endif
		}
		else if ( Type == MLOGTYPE_LOGSUC )
		{

#ifdef WINDOWSCODE
			_snprintf(filerecord.LogType,10,"[审核成功]",10);
#else	
			snprintf(filerecord.LogType,10,"[审核成功]");
#endif
		}
		else if ( Type == MLOGTYPE_LOGFAL )
		{
#ifdef WINDOWSCODE
			_snprintf(filerecord.LogType,10,"[审核失败]",10);
#else
			snprintf(filerecord.LogType,10,"[审核失败]");
#endif
		}
		_snprintf(filerecord.DateTime,21,"(%s)",tempinfo->DateTime.DateTimeToString().c_str());
		_snprintf(filerecord.RecordContent,200,"[%s]%s",Source,Content);
		filerecord.ReturnFlag[0] = 0x0D;
		filerecord.ReturnFlag[1] = 0x0A;
		

		MFile<T>::Seek(sizeof(tagLogFileHeadInfo) + m_LogFileLast * sizeof(tagLogFileRecordInfo),0);
		MFile<T>::Write((char *)&filerecord,sizeof(tagLogFileRecordInfo));

		m_LogFileLast = (m_LogFileLast + 1) % m_LogFileMaxRecord;
		if ( m_LogFileLast == m_LogFileFirst )
		{
			m_LogFileFirst = (m_LogFileLast + 1) % m_LogFileMaxRecord;
		}

		_snprintf(m_LogFileHead.First,10,"%d",m_LogFileFirst);
		_snprintf(m_LogFileHead.Last,10,"%d",m_LogFileLast);

		MFile<T>::Seek(0,0);
		MFile<T>::Write((char *)&m_LogFileHead,sizeof(tagLogFileHeadInfo));
	}

	m_Section.UnLock();
}
//#####################################################################################
 template <typename T> void MLogFile<T>::WriteView(char * Source,const char * Format,...)
{
	char										tempbuf[256];
	va_list										marker;

	va_start(marker,Format);
	_vsnprintf(tempbuf,256,Format,marker);
	va_end( marker );

	WriteReport(MLOGTYPE_VIEW,Source,tempbuf,strlen(tempbuf) + 1);
}
//#####################################################################################
 template <typename T>void MLogFile<T>::WriteInfo(char * Source,const char * Format,...)
{
	char										tempbuf[256];
	va_list										marker;

	va_start(marker,Format);
	_vsnprintf(tempbuf,256,Format,marker);
	va_end( marker );

	WriteReport(MLOGTYPE_INFO,Source,tempbuf,strlen(tempbuf) + 1);
}
//#####################################################################################
 template <typename T> void MLogFile<T>::WriteWarning(char * Source,const char * Format,...)
{
	char										tempbuf[256];
	va_list										marker;

	va_start(marker,Format);
	_vsnprintf(tempbuf,256,Format,marker);
	va_end( marker );

	WriteReport(MLOGTYPE_WARNING,Source,tempbuf,strlen(tempbuf) + 1);
}
//#####################################################################################
 template <typename T> void MLogFile<T>::WriteError(char * Source,const char * Format,...)
{
	char										tempbuf[256];
	va_list										marker;

	va_start(marker,Format);
	_vsnprintf(tempbuf,256,Format,marker);
	va_end( marker );

	WriteReport(MLOGTYPE_ERROR,Source,tempbuf,strlen(tempbuf) + 1);
}
//#####################################################################################
 template <typename T> void MLogFile<T>::WriteLogSuc(char * Source,const char * Format,...)
{
	char										tempbuf[256];
	va_list										marker;

	va_start(marker,Format);
	_vsnprintf(tempbuf,256,Format,marker);
	va_end( marker );

	WriteReport(MLOGTYPE_LOGSUC,Source,tempbuf,strlen(tempbuf) + 1);
}
//#####################################################################################
 template <typename T> void MLogFile<T>::WriteLogFal(char * Source,const char * Format,...)
{
	char										tempbuf[256];
	va_list										marker;

	va_start(marker,Format);
	_vsnprintf(tempbuf,256,Format,marker);
	va_end( marker );

	WriteReport(MLOGTYPE_LOGFAL,Source,tempbuf,strlen(tempbuf) + 1);
}
//#####################################################################################
 template <typename T> void MLogFile<T>::WriteDebug(char * Source,char * Content,char * DebugInfo,unsigned int  InSize)
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
//#####################################################################################
 template <typename T> int  MLogFile<T>::GetLogInfo(unsigned char * Type,MString<T> * Source,MString<T> * Content,MDateTime<T> * DateTime)
{
	tagLogFileMemoryInfo<T>						tempinfo;
	char										tempbuf[256];
	register int								errorcode;

	if ( (errorcode = m_RecordData.GetData((char *)&tempinfo,sizeof(tagLogFileMemoryInfo<T>))) <= 0 )
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
//#####################################################################################
 template <typename T> void MLogFile<T>::WriteAddtionLog(const char * Format,...)
{
	MFile<T>							fileptr;
	MString<T>										filepath;
	char										tempbuf[256];
	va_list										marker;

	//filepath = GetApplicationFilePath<char>() + "addtion.log";
	filepath = "./addtion.log";
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

	_snprintf(tempbuf,256,"%s\r\n",MDateTime<T>::Now().DateTimeToString().c_str());

	fileptr.Write(tempbuf,strlen(tempbuf));

	fileptr.Close();
}
//#####################################################################################
/*main()
{     int i;
      MLogFile log;
      log.Instance("test.log");
      MString info("日志警告");
      for(i=0; i<=100; i++)
      {        info="难得桂花香"; 
               info+=i;
        log.WriteInfo("aaa", info.c_str());
      }
      
}*/

#endif
