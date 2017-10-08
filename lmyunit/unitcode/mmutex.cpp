//--------------------------------------------------------------------------------------------------------------------------------
#include "mmutex.h"
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MCriticalSection,MObject)

END_LMYUNIT
//........................................................................
MCriticalSection::MLock::MLock(MCriticalSection& section )
						:m_section( section ) 
{
	m_section.Lock();
}
//........................................................................
MCriticalSection::MLock::~MLock()
{
	m_section.UnLock();
}
//................................................................................................................................
MCriticalSection::MCriticalSection(void)
{
#ifdef WINDOWSCODE
	::InitializeCriticalSection(&m_Section);
#else	
	pthread_mutex_init(&m_Section,NULL);
	m_LastThreadId = (unsigned long)(-1);
	m_nLockCount = 0;
#endif
}
//................................................................................................................................
MCriticalSection::~MCriticalSection()
{
#ifdef WINDOWSCODE
	::DeleteCriticalSection(&m_Section);
#else
	pthread_mutex_destroy(&m_Section);
	m_LastThreadId = (unsigned long)(-1);
#endif
}
//................................................................................................................................
void MCriticalSection::Lock(void)
{
#ifdef WINDOWSCODE
	::EnterCriticalSection(&m_Section);
#else
	unsigned long			errorcode;
	errorcode = (unsigned long)pthread_self();
	// 如果不是本线程前面锁定的
	// 则等待直到锁定
	// 判断的同时, m_curLockThread可能被其他线程改变
	// 但其他线程一定不会将m_curLockThread改变成与本线程相同的标识
	// 并且该标识是一个整数, 在一个机器指令内完成改变, 不考虑与副本的不同
	if ( m_LastThreadId != errorcode )
	{
		//不是同一个线程
		pthread_mutex_lock(&m_Section);

	}
	m_nLockCount++;
	m_LastThreadId = errorcode;
#endif
}
//................................................................................................................................
void MCriticalSection::UnLock(void)
{
#ifdef WINDOWSCODE
	::LeaveCriticalSection(&m_Section);
#else
	if(--m_nLockCount <= 0)
	{
		m_nLockCount = 0;
		m_LastThreadId = (pthread_t)-1;
		pthread_mutex_unlock(&m_Section);
	}
#endif
}
//--------------------------------------------------------------------------------------------------------------------------------
MLocalSection::MLocalSection(void)
{
	m_SectionPtr = NULL;
}
//................................................................................................................................
MLocalSection::~MLocalSection()
{
	UnLock();
}
//................................................................................................................................
void MLocalSection::AttchLock(MCriticalSection * In)
{
	m_SectionPtr = In;
	if ( m_SectionPtr != NULL )
	{
		m_SectionPtr->Lock();
	}
}
//................................................................................................................................
void MLocalSection::UnLock(void)
{
	if ( m_SectionPtr != NULL )
	{
		m_SectionPtr->UnLock();
		m_SectionPtr = NULL;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MMrSwSection,MObject)

	ERROR_DEFINE(ERROR_MMRSWSECTION_READFAL,"MMrSwSection","进入临界区读操作失败[等待超时]")
	ERROR_DEFINE(ERROR_MMRSWSECTION_WRITEFAL,"MMrSwSection","进入临界区写操作失败[等待超时]")

END_LMYUNIT
//........................................................................
MMrSwSection::MRLock::MRLock(MMrSwSection& section, int& nRlt,  unsigned short nTry ) 
					:m_section( section )
{
	m_bLocked = ((nRlt = m_section.LockRead( nTry )) > 0); 
}
//........................................................................
MMrSwSection::MRLock::~MRLock()
{ 
	if( m_bLocked ) m_section.UnLock(); 
}
//........................................................................
MMrSwSection::MWLock::MWLock( MMrSwSection& section, int& nRlt,  unsigned short nTry )
					:m_section( section )
{	
	m_bLocked = ((nRlt = m_section.LockWrite( nTry )) >0); 
}
//........................................................................
MMrSwSection::MWLock::~MWLock()
{ 
	if( m_bLocked ) m_section.UnLock(); 
}

//................................................................................................................................
MMrSwSection::MMrSwSection(void)
{
#ifdef WINDOWSCODE
	::InitializeCriticalSection(&m_Section);
#else
	pthread_mutex_init(&m_Section,NULL);
#endif
	m_Active = 0;
	m_WaitWriteCount = 0;
}
//................................................................................................................................
MMrSwSection::~MMrSwSection()
{
#ifdef WINDOWSCODE
	::DeleteCriticalSection(&m_Section);
#else
	pthread_mutex_destroy(&m_Section);
#endif
}
//................................................................................................................................
int  MMrSwSection::LockRead(unsigned short TryTime)
{
#ifdef WINDOWSCODE
	register int						trytime = 0;

	while ( 1 )
	{
		::EnterCriticalSection(&m_Section);

		if ( m_Active >= 0 && m_WaitWriteCount == 0 )
		{
			m_Active ++;
			::LeaveCriticalSection(&m_Section);
			return(1);
		}
		else
		{
			::LeaveCriticalSection(&m_Section);
			trytime ++;

			if ( TryTime != 0xFFFF && trytime >= TryTime )
			{
				return(ERROR_MMRSWSECTION_READFAL);
			}
		}

		Sleep(50);
	}
#else
	register int						trytime = 0;

	while ( 1 )
	{
		pthread_mutex_lock(&m_Section);

		if ( m_Active >= 0 && m_WaitWriteCount == 0 )
		{
			m_Active ++;
			pthread_mutex_unlock(&m_Section);
			return(1);
		}
		else
		{
			pthread_mutex_unlock(&m_Section);
			trytime ++;

			if ( TryTime != 0xFFFF && trytime >= TryTime )
			{
				return(ERROR_MMRSWSECTION_READFAL);
			}
		}

		usleep(50000);
	}
#endif
}
//................................................................................................................................
int  MMrSwSection::LockWrite(unsigned short TryTime)
{
#ifdef WINDOWSCODE
	bool						flag = false;
	register int				trytime = 0;

	while ( 1 )
	{
		::EnterCriticalSection(&m_Section);

		if ( m_Active == 0 )
		{
			m_Active = -1;
			if ( flag == true )
			{
				m_WaitWriteCount --;	
			}

			::LeaveCriticalSection(&m_Section);
			return(1);
		}
		else
		{
			if ( flag == false )
			{
				m_WaitWriteCount ++;
				flag = true;
			}

			::LeaveCriticalSection(&m_Section);
			trytime ++;

			if ( TryTime != 0xFFFF && trytime >= TryTime )
			{
				return(ERROR_MMRSWSECTION_WRITEFAL);
			}
		}

		Sleep(50);
	}
#else
	bool						flag = false;
	register int				trytime = 0;

	while ( 1 )
	{
		pthread_mutex_lock(&m_Section);

		if ( m_Active == 0 )
		{
			m_Active = -1;
			if ( flag == true )
			{
				m_WaitWriteCount --;	
			}

			pthread_mutex_unlock(&m_Section);
			return(1);
		}
		else
		{
			if ( flag == false )
			{
				m_WaitWriteCount ++;
				flag = true;
			}

			pthread_mutex_unlock(&m_Section);
			trytime ++;

			if ( TryTime != 0xFFFF && trytime >= TryTime )
			{
				return(ERROR_MMRSWSECTION_WRITEFAL);
			}
		}

		usleep(50000);
	}
#endif
}
//................................................................................................................................
void MMrSwSection::UnLock(void)
{
#ifdef WINDOWSCODE
	::EnterCriticalSection(&m_Section);

	if ( m_Active < 0 )
	{
		m_Active ++;
	}
	else if ( m_Active > 0 )
	{
		m_Active --;
	}

	::LeaveCriticalSection(&m_Section);
#else
	pthread_mutex_lock(&m_Section);

	if ( m_Active < 0 )
	{
		m_Active ++;
	}
	else if ( m_Active > 0 )
	{
		m_Active --;
	}

	pthread_mutex_unlock(&m_Section);
#endif
}
//--------------------------------------------------------------------------------------------------------------------------------
MLocalComplexSection::MLocalComplexSection(void)
{
	m_Section = NULL;
}
//................................................................................................................................
MLocalComplexSection::~MLocalComplexSection()
{
	UnAttch();
}
//................................................................................................................................
int  MLocalComplexSection::AttchLockRead(MComplexMrSwSection * section,unsigned long TimeOut)
{
	m_Section = section;
	return(m_Section->LockRead(TimeOut));
}
//................................................................................................................................
int  MLocalComplexSection::AttchLockWrite(MComplexMrSwSection * section,unsigned long TimeOut)
{
	m_Section = section;
	return(m_Section->LockWrite(TimeOut));
}
//................................................................................................................................
void MLocalComplexSection::UnAttch(void)
{
	if ( m_Section != NULL )
	{
		m_Section->UnLock();
		m_Section = NULL;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MComplexMrSwSection,MObject)

	ERROR_DEFINE(ERROR_MCOMPLEXMRSWSECTION_READFAL,"MComplexMrSwSection","进入临界区读操作失败[等待超时]")
	ERROR_DEFINE(ERROR_MCOMPLEXMRSWSECTION_WRITEFAL,"MComplexMrSwSection","进入临界区写操作失败[等待超时]")

END_LMYUNIT
//........................................................................
MComplexMrSwSection::MRLock::MRLock(MComplexMrSwSection& section, int& nRlt, unsigned long nTO ) 
					:m_section( section )
{
	m_bLocked = ( (nRlt = m_section.LockRead( nTO )) > 0 ); 
}
//........................................................................
MComplexMrSwSection::MRLock::~MRLock()
{ 
	if( m_bLocked ) m_section.UnLock(); 
}
//........................................................................
MComplexMrSwSection::MWLock::MWLock( MComplexMrSwSection& section, int& nRlt, unsigned long nTO )
					:m_section( section )
{	
	m_bLocked = ( (nRlt = m_section.LockWrite( nTO )) > 0 ); 
}
//........................................................................
MComplexMrSwSection::MWLock::~MWLock()
{ 
	if( m_bLocked ) m_section.UnLock(); 
}
//................................................................................................................................
MComplexMrSwSection::MComplexMrSwSection(void)
{
#ifdef WINDOWSCODE
	m_WaitReadSem = ::CreateSemaphore(NULL,0,MAXLONG,NULL);
	assert(m_WaitReadSem != NULL);

	m_WaitWriteSem = ::CreateSemaphore(NULL,0,MAXLONG,NULL);
	assert(m_WaitWriteSem != NULL);

	::InitializeCriticalSection(&m_Section);
	m_WaitReadCount = 0;
	m_WaitWriteCount = 0;
	m_Active = 0;
#else
	pthread_rwlock_init(&m_Section,NULL);
#endif
}
//................................................................................................................................
MComplexMrSwSection::~MComplexMrSwSection()
{
#ifdef WINDOWSCODE
	::DeleteCriticalSection(&m_Section);
	::CloseHandle(m_WaitReadSem);
	::CloseHandle(m_WaitWriteSem);
#else
	pthread_rwlock_destroy(&m_Section);
#endif
}
//................................................................................................................................
int  MComplexMrSwSection::LockRead(unsigned long TimeOut)
{
#ifdef WINDOWSCODE
	register bool			flag;
	register unsigned long	errorcode;

	::EnterCriticalSection(&m_Section);

	flag = ( m_WaitWriteCount > 0 ) || ( m_Active < 0 );
	if ( flag )
	{
		m_WaitReadCount ++;
	}
	else
	{
		m_Active ++;
	}

	::LeaveCriticalSection(&m_Section);

	if ( flag )
	{
		errorcode = ::WaitForSingleObject(m_WaitReadSem,TimeOut);
		if ( errorcode == WAIT_TIMEOUT || errorcode == WAIT_FAILED )
		{
			return(ERROR_MCOMPLEXMRSWSECTION_READFAL);
		}
	}

	return(1);
#else
	return ( (pthread_rwlock_rdlock(&m_Section) == 0) ? 1 : -1 );
#endif
}
//................................................................................................................................
int  MComplexMrSwSection::LockWrite(unsigned long TimeOut)
{
#ifdef WINDOWSCODE
	register bool					flag;
	register unsigned long			errorcode;

	::EnterCriticalSection(&m_Section);

	flag = ( m_Active != 0 );
	if ( flag )
	{
		m_WaitWriteCount ++;
	}
	else
	{
		m_Active = -1;
	}

	::LeaveCriticalSection(&m_Section);

	if ( flag )
	{
		errorcode = ::WaitForSingleObject(m_WaitWriteSem,TimeOut);
		if ( errorcode == WAIT_TIMEOUT || errorcode == WAIT_FAILED )
		{
			return(ERROR_MCOMPLEXMRSWSECTION_WRITEFAL);
		}
	}

	return(1);
#else
	return ( (pthread_rwlock_wrlock(&m_Section)== 0) ? 1 : -1 );
#endif
}
//................................................................................................................................
void MComplexMrSwSection::UnLock(void)
{
#ifdef WINDOWSCODE
	register HANDLE					temphandle = NULL;
	register int					tempcount = 1;

	::EnterCriticalSection(&m_Section);

	if ( m_Active > 0 )
	{
		m_Active --;
	}
	else if ( m_Active < 0 )
	{
		m_Active ++;
	}

	if ( m_Active == 0 )
	{
		if ( m_WaitWriteCount > 0 )
		{
			m_Active = -1;
			m_WaitWriteCount --;
			temphandle = m_WaitWriteSem;
		}
		else if ( m_WaitReadCount > 0 )
		{
			tempcount = m_WaitReadCount;
			m_Active = m_WaitReadCount;
			m_WaitReadCount = 0;
			temphandle = m_WaitReadSem;
		}
	}

	::LeaveCriticalSection(&m_Section);

	if ( temphandle != NULL )
	{
		::ReleaseSemaphore(temphandle,tempcount,NULL);
	}
#else
	pthread_rwlock_unlock(&m_Section);
#endif
}
//========================================================================
//************************************************************************
//========================================================================
MSemaphore::MLock::MLock( MSemaphore& sem, bool& rlt, unsigned long lTimeOut ):m_sem( sem )
{
	m_bLocked = rlt = m_sem.Lock( lTimeOut );
}
//........................................................................
MSemaphore::MLock::~MLock()
{
	if( m_bLocked ) m_sem.UnLock();
}
//........................................................................
MSemaphore::MSemaphore( void )
{
#ifdef WINDOWSCODE
	 m_hSem = NULL;
#else
#endif //WINDOWSCODE
}
//........................................................................
MSemaphore::~MSemaphore( void )
{
#ifdef WINDOWSCODE
	if( m_hSem )
		::CloseHandle( m_hSem );
	m_hSem = NULL;
#else
#endif //WINDOWSCODE
}
//........................................................................
int	 MSemaphore::Instance( long lInitialCount, long lMaxCount )
{
#ifdef WINDOWSCODE
	if( m_hSem )
		::CloseHandle( m_hSem );
	m_hSem = ::CreateSemaphore( NULL, lInitialCount, lMaxCount, NULL );
	return ( m_hSem == NULL ? -1 : 1 );
#else
	return (1);
#endif //WINDOWSCODE
}
//........................................................................
bool MSemaphore::Lock( unsigned long lTimeOut )
{
#ifdef WINDOWSCODE
	if (::WaitForSingleObject(m_hSem, lTimeOut) == WAIT_OBJECT_0)
		return (true);
	else
		return (false);
#else
	return (true);
#endif //WINDOWSCODE
}
//........................................................................
void MSemaphore::UnLock( long lCount )
{
#ifdef WINDOWSCODE
	::ReleaseSemaphore( m_hSem, lCount, NULL );
#else
	return;
#endif //WINDOWSCODE
}
//--------------------------------------------------------------------------------------------------------------------------
MWaitEvent::MWaitEvent(void)
{
#ifdef WINDOWSCODE
	m_Handle = NULL;
#else
	pthread_cond_init(&m_Handle,NULL);
#endif
}
//..........................................................................................................................
MWaitEvent::~MWaitEvent()
{
#ifdef WINDOWSCODE
	Release();
#else
	pthread_cond_destroy(&m_Handle);
#endif
}
//..........................................................................................................................
int  MWaitEvent::Instance(void)
{
#ifdef WINDOWSCODE
	Release();
	
	if ( (m_Handle = ::CreateEvent(NULL,FALSE,FALSE,NULL)) == NULL )
	{
		return(ERROR_SYSTEM(GetLastError()));
	}
#else
	
#endif
	
	return(1);
}
//..........................................................................................................................
void MWaitEvent::Release(void)
{
#ifdef WINDOWSCODE
	if ( m_Handle != NULL )
	{
		::CloseHandle(m_Handle);
		m_Handle = NULL;
	}
#else
	
#endif
}
//..........................................................................................................................
void MWaitEvent::ActiveEvent(void)
{
#ifdef WINDOWSCODE
	::SetEvent(m_Handle);
#else
	pthread_cond_signal(&m_Handle);
#endif
}
//..........................................................................................................................
int  MWaitEvent::WaitUntilActive(unsigned long MSec)
{
#ifdef WINDOWSCODE
	register int				errorcode;
	
	errorcode = ::WaitForSingleObject(m_Handle,MSec);
	if ( errorcode == WAIT_TIMEOUT || errorcode == WAIT_FAILED )
	{
		return(-1);
	}
	else
	{
		return(1);
	}
#else
	struct timespec				temptime;
	
	temptime.tv_sec = MSec/1000;
	temptime.tv_nsec = (MSec%1000)*1e6;
	//temptime = MSec;
	pthread_cond_timedwait(&m_Handle,NULL,&temptime);
	
	return(1);
#endif
}
//--------------------------------------------------------------------------------------------------------------------------
