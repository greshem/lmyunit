//#####################################################################################
//                  ;;;,
//        ,;;;;;: ,;;;:.,;..
//         :;;"`,;;;;;;"":;;					��Ԫ���ƣ���־�ļ���д����
//      ..;;:  .;;,.;;:',;;"
//    ,;;;;;;" :;`',;",;;"						��д���ڣ�2010��8��12 ת����stl
//   :" ,;:` , `:.;;;;;'
//    ,;;;,;:;;,;;;, ,;							��д��Ա��qianzj
//   :;;;"` `:;;;;;,;,.;.
//   '""   .;;`.;";:;;;;` ;,					��ע��Ϣ��
//       .;"`  ::. '   .,;;;
//      ""     ';;;;;;;;;;`
//#####################################################################################
#ifndef __LmyUnitMLogFileH__
#define __LmyUnitMLogFileH__
//#####################################################################################
//����ͷ�ļ�
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
//Windows����ϵͳ
//#####################################################################################
#else
//#####################################################################################
//Linux����ϵͳ
#include "stdlib.h"
//#####################################################################################
#endif
//#####################################################################################
#pragma pack(1)
//#####################################################################################
enum
{
	MLOGTYPE_VIEW = 0,									//��ˮ��־
	MLOGTYPE_INFO,										//��Ϣ��־
	MLOGTYPE_WARNING,									//������־
	MLOGTYPE_ERROR,										//������־
	MLOGTYPE_LOGSUC,									//�ɹ����
	MLOGTYPE_LOGFAL,									//ʧ�����
};
//#####################################################################################
typedef struct
{
	char						MarketFlag[20];			//��־[MLOG��־�ļ�]
	char						VersionMarket[20];		//�汾����[�汾��]
	char						Version[10];			//�汾
	char						MaxRecordMarket[20];	//����¼����
	char						MaxRecord[10];			//����¼��
	char						FirstMarket[20];		//��һ����¼λ�ã�
	char						First[10];				//��һ����¼
	char						LastMarket[20];			//���һ����¼λ�ã�
	char						Last[10];				//���һ����¼
	char						InfoFlagMarket[20];		//������Ϣ��¼��
	char						InfoFlag;				//������Ϣ
	char						WarningFlagMarket[20];	//�������¼��
	char						WarningFlag;			//������
	char						ErrorFlagMarket[20];	//��������¼��
	char						ErrorFlag;				//�������
	char						LogSucFlagMarket[20];	//������˳ɹ���¼��
	char						LogSucFlag;				//������˳ɹ�
	char						LogFalFlagMarket[20];	//�������ʧ�ܼ�¼��
	char						LogFalFlag;				//�������ʧ��
	char						Reserved[9];			//����
	char						Return[2];				//�س�����
} tagLogFileHeadInfo;
//#####################################################################################
typedef struct
{
	char						LogType[10];		//����
	char						DateTime[21];		//��¼ʱ�䣬��(2004.03.28 15:30:20)
	char						RecordContent[200];	//��¼����
	char						ReturnFlag[2];		//�س����б�־
} tagLogFileRecordInfo;
//#####################################################################################
template <typename T> class  tagLogFileMemoryInfo
{
public:
	unsigned char				LogType;			//����
	MDateTime<T>					DateTime;			//��¼ʱ��
	char						Source[20];			//��Դ
	unsigned short				ContentSize;		//���ݳ���
} ;
//#####################################################################################
#pragma pack()
//#####################################################################################
#define		MLOGFILE_MEMORY_SIZE	10240				//�ڴ���־����
//#####################################################################################
#define		ERROR_MLOGFILE_FILEHEAD			(ERROR_USER(100))		//��MLogFile��������[������ļ�ͷ��]
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

//	ERROR_DEFINE(ERROR_MLOGFILE_FILEHEAD,"MLogFile","���ļ���������[������ļ�ͷ��]")

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

		if ( strncmp(m_LogFileHead.MarketFlag,"MLOG��־�ļ�",20) != 0 )
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

		strncpy(m_LogFileHead.MarketFlag,"MLOG��־�ļ�",20);
		strncpy(m_LogFileHead.VersionMarket,"�汾��",20);
		strncpy(m_LogFileHead.Version,"1.00",10);
		strncpy(m_LogFileHead.MaxRecordMarket,"����¼������",20);
		_snprintf(m_LogFileHead.MaxRecord,10,"%d",MaxRecord);
		strncpy(m_LogFileHead.FirstMarket,"��ʼλ�ã�",20);
		strncpy(m_LogFileHead.First,"0",10);
		strncpy(m_LogFileHead.LastMarket,"����λ�ã�",20);
		strncpy(m_LogFileHead.Last,"0",10);
		strncpy(m_LogFileHead.InfoFlagMarket,"��Ϣ��¼��",20);
		m_LogFileHead.InfoFlag = 'Y';
		strncpy(m_LogFileHead.WarningFlagMarket,"�����¼��",20);
		m_LogFileHead.WarningFlag = 'Y';
		strncpy(m_LogFileHead.ErrorFlagMarket,"�����¼��",20);
		m_LogFileHead.ErrorFlag = 'Y';
		strncpy(m_LogFileHead.LogSucFlagMarket,"�ɹ���ˣ�",20);
		m_LogFileHead.LogSucFlag = 'Y';
		strncpy(m_LogFileHead.LogFalFlagMarket,"ʧ����ˣ�",20);
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
			_snprintf(filerecord.LogType,10,"[��Ϣ]",10);
#else
		snprintf(filerecord.LogType,10,"[��Ϣ]");
#endif
		
		}
		else if ( Type == MLOGTYPE_WARNING )
		{

#ifdef WINDOWSCODE
			_snprintf(filerecord.LogType,10,"[����]",10);
#else
			snprintf(filerecord.LogType,10,"[����]");
#endif
		}
		else if ( Type == MLOGTYPE_ERROR )
		{

#ifdef WINDOWSCODE
			_snprintf(filerecord.LogType,10,"[����]",10);
#else
			snprintf(filerecord.LogType,10,"[����]");
#endif
		}
		else if ( Type == MLOGTYPE_LOGSUC )
		{

#ifdef WINDOWSCODE
			_snprintf(filerecord.LogType,10,"[��˳ɹ�]",10);
#else	
			snprintf(filerecord.LogType,10,"[��˳ɹ�]");
#endif
		}
		else if ( Type == MLOGTYPE_LOGFAL )
		{
#ifdef WINDOWSCODE
			_snprintf(filerecord.LogType,10,"[���ʧ��]",10);
#else
			snprintf(filerecord.LogType,10,"[���ʧ��]");
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

	_snprintf(tempbuf,256,"%s[DEBUG�� ",Content);
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
      MString info("��־����");
      for(i=0; i<=100; i++)
      {        info="�ѵù���"; 
               info+=i;
        log.WriteInfo("aaa", info.c_str());
      }
      
}*/

#endif
