//#####################################################################################
//#####################################################################################
#ifndef __LmyUnitMThreadH__
#define __LmyUnitMThreadH__
//#####################################################################################
//公共头文件
//#include "MObject.h"
#include "MString.hpp"
#include "MDateTime.hpp"
//#####################################################################################
#ifdef WINDOWSCODE
//#####################################################################################
//Windows操作系统
//#####################################################################################
#else
//#####################################################################################
//Linux操作系统
#include "pthread.h"
//#####################################################################################
#endif
//#####################################################################################
#define		MAX_THREAD_REFRESHTIME				20000		//线程最大延迟时间
//#####################################################################################
typedef void tagFunInterface_ThreadWriteReport(char * InBuf);
//#####################################################################################
template <typename T> class MThread// : public MObject
{
protected:
	static MThread			*	staticFirstThreadPtr;
	static MCounter<T>				staticCheckThreadTime;
protected:

#ifdef WINDOWSCODE
	HANDLE						m_ThreadHandle;
#else
	pthread_t					m_ThreadHandle;
#endif
	
	bool						m_ActiveThreadFlag;
	char						m_ThreadName[32];
	MCounter<T>					m_RefreshTime;
	unsigned long				m_iTOCount;			
	MThread<T>					*	m_NextThreadPtr;
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

//	DECLARE_LMYUNIT(MThread)
};
//#####################################################################################
//#####################################################################################

//#####################################################################################
//#include "MThread.h"

#ifdef WINDOWSCODE
	
	#include "process.h"
		
#else
	
#endif
//#####################################################################################
////BEGIN_LMYUNIT(MThread,MObject)

//END_LMYUNIT
//#####################################################################################
template <typename T> MThread<T>			*	MThread<T>::staticFirstThreadPtr = NULL;
template <typename T> MCounter<T>		MThread<T>::staticCheckThreadTime;
//#####################################################################################
template <typename T> MThread<T>::MThread(void)
{
#ifdef WINDOWSCODE
	m_ThreadHandle = NULL;
#else
	
#endif
	m_ThreadHandle = 0;
	
	m_ActiveThreadFlag = false;
	strncpy(m_ThreadName,"未命名线程",32);
	
	m_NextThreadPtr = staticFirstThreadPtr;
	staticFirstThreadPtr = this;

	m_AddtionData = 0xFFFFFFFF;
	m_iTOCount	= 0l;
	staticCheckThreadTime.GetCurTickCount();
}
//#####################################################################################
template <typename T> MThread<T>::~MThread()
{
#ifdef WINDOWSCODE
#else
#endif

	StopThread();
}
//#####################################################################################
 template <typename T>int  MThread<T>::StartThread(char * ThreadName,void * (__stdcall * ThreadFun)(void *),void * Param,bool PauseFlag)
{
#ifdef WINDOWSCODE

	register unsigned long				errorcode;
	register unsigned long				pauseparam = 0;

	if ( PauseFlag == true )
	{
		pauseparam = CREATE_SUSPENDED;
	}

	strncpy(m_ThreadName,ThreadName,32);
	m_ThreadHandle = (HANDLE)_beginthreadex(	0,
												0,
												(unsigned int (__stdcall *)(void *))ThreadFun,
												Param,
												pauseparam,
												(unsigned int *)&errorcode	);
	if ( m_ThreadHandle == NULL )
	{
		m_ActiveThreadFlag = false;
//		return(ERROR_SYSTEM(GetLastError()));
			return -1;
	}

	if ( PauseFlag == true )
	{
		m_ActiveThreadFlag = false;
	}
	else
	{
		m_ActiveThreadFlag = true;
	}

	return(1);
#else
	
	//register unsigned long				errorcode;
	//register unsigned long				pauseparam = 0;

	strncpy(m_ThreadName,ThreadName,32);
	if ( pthread_create(&m_ThreadHandle,NULL,ThreadFun,Param) != 0 )
	{
		m_ActiveThreadFlag = false;
		//return(ERROR_SYSTEM(GetLastError()));
		return -1;
	}
	
	m_ActiveThreadFlag = true;

	return(1);
#endif
}
//#####################################################################################
template <typename T>  void MThread<T>::StopThread(void)
{
#ifdef WINDOWSCODE
	register int						errorcode;

	if ( m_ThreadHandle != NULL )
	{
		errorcode = ::WaitForSingleObject(m_ThreadHandle,5000);
		if ( errorcode == WAIT_TIMEOUT || errorcode == WAIT_FAILED )
		{
			::TerminateThread(m_ThreadHandle,0);
		}
		::CloseHandle(m_ThreadHandle);
		m_ThreadHandle = NULL;
	}
	m_ActiveThreadFlag = false;
#else
	if ( m_ThreadHandle != 0 )
	{
		pthread_join(m_ThreadHandle,NULL);
		m_ThreadHandle = 0;
	}
	m_ActiveThreadFlag = false;
#endif
}
//#####################################################################################
template <typename T> int  MThread<T>::PauseThread(void)
{
#ifdef WINDOWSCODE
	if ( ::SuspendThread(m_ThreadHandle) == 0xFFFFFFFF )
	{
//		return(ERROR_SYSTEM(GetLastError()));
				return -1;
	}

	m_ActiveThreadFlag = false;
	return(1);
#else
	return(1);
#endif
}
//#####################################################################################
 template <typename T>int  MThread<T>::ResumeThread(void)
{
#ifdef WINDOWSCODE
	if ( ::ResumeThread(m_ThreadHandle) == 0xFFFFFFFF )
	{
//		return(ERROR_SYSTEM(GetLastError()));
				return -1;
	}

	m_ActiveThreadFlag = true;
	return(1);
#else
	return(1);
#endif
}
//#####################################################################################
 template <typename T> bool MThread<T>::IsEmpty(void)
{
#ifdef WINDOWSCODE
	if ( m_ThreadHandle == NULL )
	{
		return(true);
	}
	else
	{
		return(false);
	}
#else
	return(m_ActiveThreadFlag);
#endif
}
//#####################################################################################
 template <typename T> bool MThread<T>::IsActive(void)
{
	return(m_ActiveThreadFlag);
}
//#####################################################################################
 template <typename T> void MThread<T>::RefreshThread(void)
{
	m_RefreshTime.GetCurTickCount();
}
//#####################################################################################
 template <typename T> void MThread<T>::Sleep(unsigned long Time)
{
#ifdef WINDOWSCODE
	::Sleep(Time);
#else
	usleep(Time*1000);
#endif
}
//#####################################################################################
 template <typename T> unsigned long MThread<T>::GetAddtionData(void)
{
	return(m_AddtionData);
}
//#####################################################################################
 template <typename T> void MThread<T>::SetAddtionData(unsigned long In)
{
	m_AddtionData = In;
}
//#####################################################################################
 template <typename T> void MThread<T>::CheckThreadRefreshTime(tagFunInterface_ThreadWriteReport * In)
{
	MThread<T>				*	threadptr;
	char					tempbuf[256];
	register int			errorcode;

	if ( staticCheckThreadTime.GetDuration() >= (MAX_THREAD_REFRESHTIME / 2) )
	{
		threadptr = staticFirstThreadPtr;
		while ( threadptr != NULL )
		{
			if ( threadptr->m_ThreadHandle != 0 )
			{
				errorcode = threadptr->m_RefreshTime.GetDuration();
				if( errorcode < MAX_THREAD_REFRESHTIME && threadptr->m_iTOCount != 0 )
				{
					threadptr->m_iTOCount = 0l;
					_snprintf( tempbuf, 255, "线程[%s]恢复正常[附加数据：%d]",threadptr->m_ThreadName,(int )threadptr->m_AddtionData);
					In( tempbuf );
				}
				if ( errorcode >= MAX_THREAD_REFRESHTIME )
				{
					threadptr->m_iTOCount++;
					if( (unsigned long)errorcode >= min( (unsigned long)10*60*1000, threadptr->m_iTOCount*MAX_THREAD_REFRESHTIME ) )
					{
						_snprintf(tempbuf,256,"线程[%s]已经停止响应%d毫秒[附加数据：%d]",threadptr->m_ThreadName,errorcode,(int) threadptr->m_AddtionData);
						In(tempbuf);
					}
				}
			}
			
			threadptr = threadptr->m_NextThreadPtr;
		}

		staticCheckThreadTime.GetCurTickCount();
	}
}
//#####################################################################################

#endif
