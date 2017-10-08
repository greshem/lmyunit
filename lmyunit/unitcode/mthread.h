//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMThreadH__
#define __LmyUnitMThreadH__
//--------------------------------------------------------------------------------------------------------------------------------
//公共头文件
#include "mobject.h"
#include "mdatetime.h"
//................................................................................................................................
#ifdef WINDOWSCODE
//................................................................................................................................
//Windows操作系统
//................................................................................................................................
#else
//................................................................................................................................
//Linux操作系统
#include "pthread.h"
//................................................................................................................................
#endif
//--------------------------------------------------------------------------------------------------------------------------------
#define		MAX_THREAD_REFRESHTIME				20000		//线程最大延迟时间
//................................................................................................................................
typedef void tagFunInterface_ThreadWriteReport(char * InBuf);
//................................................................................................................................
class MThread : public MObject
{
protected:
	static MThread			*	staticFirstThreadPtr;
	static MCounter				staticCheckThreadTime;
protected:

#ifdef WINDOWSCODE
	HANDLE						m_ThreadHandle;
#else
	pthread_t					m_ThreadHandle;
#endif
	
	bool						m_ActiveThreadFlag;
	char						m_ThreadName[32];
	MCounter					m_RefreshTime;
	unsigned long				m_iTOCount;			
	MThread					*	m_NextThreadPtr;
	unsigned long				m_AddtionData;

public:
	MThread(void);
	virtual ~MThread();
public:
	int  StartThread(char * ThreadName,void * (__stdcall * ThreadFun)(void *),void * Param,bool PauseFlag = false);
	void StopThread(void);
public:
	int  PauseThread(void);
	int  ResumeThread(void);
public:
	bool IsEmpty(void);
	bool IsActive(void);
public:
	void RefreshThread(void);
public:
	unsigned long GetAddtionData(void);
	void SetAddtionData(unsigned long In);
public:
	static void Sleep(unsigned long Time);
	static void CheckThreadRefreshTime(tagFunInterface_ThreadWriteReport * In);

	DECLARE_LMYUNIT(MThread)
};
//--------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------

