//--------------------------------------------------------------------------------------------------------------------------------
//                  ;;;,
//        ,;;;;;: ,;;;:.,;..
//         :;;"`,;;;;;;"":;;					单元名称：日志文件读写处理
//      ..;;:  .;;,.;;:',;;"
//    ,;;;;;;" :;`',;",;;"						编写日期：2004年5月20
//   :" ,;:` , `:.;;;;;'
//    ,;;;,;:;;,;;;, ,;							编写人员：richtech
//   :;;;"` `:;;;;;,;,.;.
//   '""   .;;`.;";:;;;;` ;,					备注信息：
//       .;"`  ::. '   .,;;;
//      ""     ';;;;;;;;;;`
//--------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMLogFileH__
#define __LmyUnitMLogFileH__
//--------------------------------------------------------------------------------------------------------------------------------
//公共头文件
#include "mfile.h"
#include "mobject.h"
#include "mdatastruct.h"
#include "mstring.h"
#include "mmutex.h"
#include "mdatetime.h"
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
enum
{
	MLOGTYPE_VIEW = 0,									//流水日志
	MLOGTYPE_INFO,										//信息日志
	MLOGTYPE_WARNING,									//警告日志
	MLOGTYPE_ERROR,										//错误日志
	MLOGTYPE_LOGSUC,									//成功审核
	MLOGTYPE_LOGFAL,									//失败审核
};
//................................................................................................................................
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
//................................................................................................................................
typedef struct
{
	char						LogType[10];		//类型
	char						DateTime[21];		//记录时间，如(2004.03.28 15:30:20)
	char						RecordContent[200];	//记录内容
	char						ReturnFlag[2];		//回车换行标志
} tagLogFileRecordInfo;
//................................................................................................................................
typedef struct
{
	unsigned char				LogType;			//类型
	MDateTime					DateTime;			//纪录时间
	char						Source[20];			//来源
	unsigned short				ContentSize;		//内容长度
} tagLogFileMemoryInfo;
//--------------------------------------------------------------------------------------------------------------------------------
#pragma pack()
//--------------------------------------------------------------------------------------------------------------------------------
#define		MLOGFILE_MEMORY_SIZE	10240				//内存日志缓冲
//................................................................................................................................
#define		ERROR_MLOGFILE_FILEHEAD			(ERROR_USER(100))		//打开MLogFile发生错误[错误的文件头部]
//................................................................................................................................
class MLogFile : public MFile
{
protected:
	MCharLoopGroupMt					m_RecordData;
protected:
	MCriticalSection					m_Section;
	tagLogFileHeadInfo					m_LogFileHead;
	unsigned short						m_LogFileMaxRecord;
	unsigned short						m_LogFileFirst;
	unsigned short						m_LogFileLast;
public:
	void WriteReport(unsigned char Type,char * Source,char * Content,unsigned short InSize);
public:
	MLogFile(void);
	virtual ~MLogFile();
public:
	int  Instance(MString FileName,unsigned short MaxRecord = 1000);
	void Release(void);
public:
	void WriteView(char * Source,const char * Format,...);
	void WriteInfo(char * Source,const char * Format,...);
	void WriteWarning(char * Source,const char * Format,...);
	void WriteError(char * Source,const char * Format,...);
	void WriteLogSuc(char * Source,const char * Format,...);
	void WriteLogFal(char * Source,const char * Format,...);
	void WriteDebug(char * Source,char * Content,char * DebugInfo,unsigned short InSize);
	void WriteAddtionLog(const char * Format,...);
public:
	int  GetLogInfo(unsigned char * Type,MString * Source,MString * Content,MDateTime * DateTime);

	DECLARE_LMYUNIT(MLogFile)
};
//--------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------
