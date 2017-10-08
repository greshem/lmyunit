//--------------------------------------------------------------------------------------------------------------------------------
#include "mthread.h"

#ifdef WINDOWSCODE
	
	#include "process.h"
		
#else
	
#endif
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MThread,MObject)

END_LMYUNIT
//................................................................................................................................
MThread			*	MThread::staticFirstThreadPtr = NULL;
MCounter			MThread::staticCheckThreadTime;
//................................................................................................................................
MThread::MThread(void)
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
//................................................................................................................................
MThread::~MThread()
{
#ifdef WINDOWSCODE
#else
#endif

	StopThread();
}
//................................................................................................................................
int  MThread::StartThread(char * ThreadName,void * (__stdcall * ThreadFun)(void *),void * Param,bool PauseFlag)
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
		return(ERROR_SYSTEM(GetLastError()));
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
	
	register unsigned long				errorcode;
	register unsigned long				pauseparam = 0;

	strncpy(m_ThreadName,ThreadName,32);
	if ( pthread_create(&m_ThreadHandle,NULL,ThreadFun,Param) != 0 )
	{
		m_ActiveThreadFlag = false;
		return(ERROR_SYSTEM(GetLastError()));
	}
	
	m_ActiveThreadFlag = true;

	return(1);
#endif
}
//................................................................................................................................
void MThread::StopThread(void)
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
//................................................................................................................................
int  MThread::PauseThread(void)
{
#ifdef WINDOWSCODE
	if ( ::SuspendThread(m_ThreadHandle) == 0xFFFFFFFF )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}

	m_ActiveThreadFlag = false;
	return(1);
#else
	return(1);
#endif
}
//................................................................................................................................
int  MThread::ResumeThread(void)
{
#ifdef WINDOWSCODE
	if ( ::ResumeThread(m_ThreadHandle) == 0xFFFFFFFF )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}

	m_ActiveThreadFlag = true;
	return(1);
#else
	return(1);
#endif
}
//................................................................................................................................
bool MThread::IsEmpty(void)
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
//................................................................................................................................
bool MThread::IsActive(void)
{
	return(m_ActiveThreadFlag);
}
//................................................................................................................................
void MThread::RefreshThread(void)
{
	m_RefreshTime.GetCurTickCount();
}
//................................................................................................................................
//这是是微妙
void MThread::Sleep(unsigned long Time)
{
#ifdef WINDOWSCODE
	::Sleep(Time);
#else
	usleep(Time*1000);
#endif
}
//................................................................................................................................
unsigned long MThread::GetAddtionData(void)
{
	return(m_AddtionData);
}
//................................................................................................................................
void MThread::SetAddtionData(unsigned long In)
{
	m_AddtionData = In;
}
//................................................................................................................................
void MThread::CheckThreadRefreshTime(tagFunInterface_ThreadWriteReport * In)
{
	MThread				*	threadptr;
	char					tempbuf[256];
	register int			errorcode;

	if ( staticCheckThreadTime.GetDuration() >= (MAX_THREAD_REFRESHTIME / 2) )
	{
		threadptr = staticFirstThreadPtr;
		while ( threadptr != NULL )
		{
			if ( threadptr->m_ThreadHandle != NULL )
			{
				errorcode = threadptr->m_RefreshTime.GetDuration();
				if( errorcode < MAX_THREAD_REFRESHTIME && threadptr->m_iTOCount != 0 )
				{
					threadptr->m_iTOCount = 0l;
					_snprintf( tempbuf, 255, "线程[%s]恢复正常[附加数据：%d]",threadptr->m_ThreadName,threadptr->m_AddtionData);
					In( tempbuf );
				}
				if ( errorcode >= MAX_THREAD_REFRESHTIME )
				{
					threadptr->m_iTOCount++;
					if( (unsigned long)errorcode >= min( 10*60*1000, threadptr->m_iTOCount*MAX_THREAD_REFRESHTIME ) )
					{
						_snprintf(tempbuf,256,"线程[%s]已经停止响应%d毫秒[附加数据：%d]",threadptr->m_ThreadName,errorcode,threadptr->m_AddtionData);
						In(tempbuf);
					}
				}
			}
			
			threadptr = threadptr->m_NextThreadPtr;
		}

		staticCheckThreadTime.GetCurTickCount();
	}
}
//--------------------------------------------------------------------------------------------------------------------------------

