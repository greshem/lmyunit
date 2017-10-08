//--------------------------------------------------------------------------------------------------------------------------------
//                  ;;;,
//        ,;;;;;: ,;;;:.,;..
//         :;;"`,;;;;;;"":;;					��Ԫ���ƣ���־�ļ���д����
//      ..;;:  .;;,.;;:',;;"
//    ,;;;;;;" :;`',;",;;"						��д���ڣ�2004��5��20
//   :" ,;:` , `:.;;;;;'
//    ,;;;,;:;;,;;;, ,;							��д��Ա��richtech
//   :;;;"` `:;;;;;,;,.;.
//   '""   .;;`.;";:;;;;` ;,					��ע��Ϣ��
//       .;"`  ::. '   .,;;;
//      ""     ';;;;;;;;;;`
//--------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMLogFileH__
#define __LmyUnitMLogFileH__
//--------------------------------------------------------------------------------------------------------------------------------
//����ͷ�ļ�
#include "mfile.h"
#include "mobject.h"
#include "mdatastruct.h"
#include "mstring.h"
#include "mmutex.h"
#include "mdatetime.h"
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
enum
{
	MLOGTYPE_VIEW = 0,									//��ˮ��־
	MLOGTYPE_INFO,										//��Ϣ��־
	MLOGTYPE_WARNING,									//������־
	MLOGTYPE_ERROR,										//������־
	MLOGTYPE_LOGSUC,									//�ɹ����
	MLOGTYPE_LOGFAL,									//ʧ�����
};
//................................................................................................................................
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
//................................................................................................................................
typedef struct
{
	char						LogType[10];		//����
	char						DateTime[21];		//��¼ʱ�䣬��(2004.03.28 15:30:20)
	char						RecordContent[200];	//��¼����
	char						ReturnFlag[2];		//�س����б�־
} tagLogFileRecordInfo;
//................................................................................................................................
typedef struct
{
	unsigned char				LogType;			//����
	MDateTime					DateTime;			//��¼ʱ��
	char						Source[20];			//��Դ
	unsigned short				ContentSize;		//���ݳ���
} tagLogFileMemoryInfo;
//--------------------------------------------------------------------------------------------------------------------------------
#pragma pack()
//--------------------------------------------------------------------------------------------------------------------------------
#define		MLOGFILE_MEMORY_SIZE	10240				//�ڴ���־����
//................................................................................................................................
#define		ERROR_MLOGFILE_FILEHEAD			(ERROR_USER(100))		//��MLogFile��������[������ļ�ͷ��]
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
