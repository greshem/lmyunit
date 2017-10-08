//#####################################################################################
//#####################################################################################
#ifndef __LmyUnitMMutexH__
#define __LmyUnitMMutexH__
//#####################################################################################
//����ͷ�ļ�
//#include "MObject.h"
#include "MString.hpp"
//#####################################################################################
#ifdef WINDOWSCODE
//#####################################################################################
//Windows����ϵͳ
//#####################################################################################
#else
//#####################################################################################
//Linux����ϵͳ
#include <pthread.h>
//#####################################################################################
#endif
//#####################################################################################
template <typename T>  class MCriticalSection //: public MObject
{
public:
	class MLock
	{
	private:
		MCriticalSection& m_section;
	public:
		MLock(MCriticalSection& section );
		~MLock();
	};
protected:

#ifdef WINDOWSCODE
	CRITICAL_SECTION					m_Section;
#else
	unsigned long						m_LastThreadId;
	pthread_mutex_t						m_Section;
	int									m_nLockCount;			// ������
#endif

public:
	MCriticalSection(void);
	virtual ~MCriticalSection();
public:
	void Lock(void);
	void UnLock(void);

//	DECLARE_LMYUNIT(MCriticalSection)
};
//#####################################################################################
template <typename T> class MLocalSection
{
protected:
	MCriticalSection	<T>		*		m_SectionPtr;
public:
	MLocalSection(void);
	virtual ~MLocalSection();
public:
	void AttchLock(MCriticalSection<T> * In);
	void UnLock(void);
};
//#####################################################################################
#define		ERROR_MMRSWSECTION_READFAL		ERROR_USER(10)			//�����ٽ���������ʧ��[�ȴ���ʱ]
#define		ERROR_MMRSWSECTION_WRITEFAL		ERROR_USER(11)			//�����ٽ���д����ʧ��[�ȴ���ʱ]
//#####################################################################################
template <typename T> class MMrSwSection //: public MObject
{
public:
	class MRLock
	{
	private:
		bool		  m_bLocked;
		MMrSwSection& m_section;
	public:
		MRLock(MMrSwSection& section, int& nRlt, unsigned short nTry = 0xFFFF  );
		~MRLock();
	};
	class MWLock
	{
	private:
		bool		  m_bLocked;
		MMrSwSection& m_section;
	public:
		MWLock(MMrSwSection& section, int& nRlt, unsigned short nTry = 0xFFFF  );
		~MWLock();
	};
	
protected:

#ifdef WINDOWSCODE
	CRITICAL_SECTION					m_Section;
#else
	pthread_mutex_t						m_Section;
#endif
	int									m_Active;
	unsigned short						m_WaitWriteCount;

public:
	MMrSwSection(void);
	virtual ~MMrSwSection();
public:
	int  LockRead(unsigned short TryTime = 0xFFFF);
	int  LockWrite(unsigned short TryTime = 0xFFFF);
	void UnLock(void);

//	DECLARE_LMYUNIT(MMrSwSection)
};
//#####################################################################################
#define		ERROR_MCOMPLEXMRSWSECTION_READFAL		ERROR_USER(12)			//�����ٽ���������ʧ��[�ȴ���ʱ]
#define		ERROR_MCOMPLEXMRSWSECTION_WRITEFAL		ERROR_USER(13)			//�����ٽ���д����ʧ��[�ȴ���ʱ]
//#####################################################################################
template <typename T> class MComplexMrSwSection //: public MObject
{
public:
	class MRLock
	{
	private:
		bool				 m_bLocked;
		MComplexMrSwSection& m_section;
	public:
		MRLock(MComplexMrSwSection& section, int& nRlt, unsigned long nTO = 5000  );
		~MRLock();
	};
	class MWLock
	{
	private:
		bool				 m_bLocked;
		MComplexMrSwSection& m_section;
	public:
		MWLock(MComplexMrSwSection& section, int& nRlt, unsigned long nTO = 0xFFFFFFFF  );
		~MWLock();
	};
	
protected:

#ifdef WINDOWSCODE
	CRITICAL_SECTION					m_Section;
	HANDLE								m_WaitReadSem;
	HANDLE								m_WaitWriteSem;
	int									m_Active;
	int									m_WaitReadCount;
	int									m_WaitWriteCount;
#else
	pthread_rwlock_t					m_Section;
#endif

public:
	MComplexMrSwSection(void);
	virtual ~MComplexMrSwSection();
public:
	int  LockRead(unsigned long TimeOut = 5000);
	int  LockWrite(unsigned long TimeOut = 0xFFFFFFFF);
	void UnLock(void);

//	DECLARE_LMYUNIT(MComplexMrSwSection)
};

//#####################################################################################
template <typename T> class MLocalComplexSection
{
protected:
	MComplexMrSwSection <T> 			*	m_Section;
public:
	MLocalComplexSection(void);
	virtual ~MLocalComplexSection();
public:
	int  AttchLockRead(MComplexMrSwSection<T> * section,unsigned long TimeOut = 5000);
	int  AttchLockWrite(MComplexMrSwSection<T> * section,unsigned long TimeOut = 0xFFFFFFFF);
	void UnAttch(void);
};

//#####################################################################################
//========================================================================
//************************************************************************
//========================================================================

template <typename T> class MSemaphore //: public MObject
{
public:
	class MLock
	{
	private:
		bool		m_bLocked;
		MSemaphore& m_sem;

	public:
		MLock( MSemaphore& sem, bool& rlt, unsigned long lTimeOut = 0xFFFFFFFF  );
		~MLock( void );
	};

private:

#ifdef WINDOWSCODE
	HANDLE							m_hSem;
#else
#endif //WINDOWSCODE
	
public:
	MSemaphore( void );
	~MSemaphore( void );
	
public:
	int	 Instance( long lInitialCount, long lMaxCount );

public:
	bool Lock( unsigned long lTimeOut = 0xFFFFFFFF );
	void UnLock( long lCount = 1 );
	
	friend class MSemaphore::MLock;
};
//#####################################################################################
//�ȴ��¼�����Ȼ�������ڶ�����̣���������¼����ƣ�����Ϊ�˼���Linux��������Ҫ���ڽ����ڲ������̼�ʹ�õ�����պ������
//��Ҫ������ͷǼ���������������sleep���������ܹ�������Ӧ��
template <typename T> class MWaitEvent
{
protected:
#ifdef WINDOWSCODE
	HANDLE									m_Handle;
#else
	pthread_cond_t							m_Handle;
	pthread_mutex_t							m_Section;
#endif
public:
	//������������
	MWaitEvent(void);
	virtual ~MWaitEvent();
public:
	int  Instance(void);
	void Release(void);
public:
	//������¼�
	void ActiveEvent(void);
	//�ȴ�ֱ���¼��������ʱ
	int  WaitUntilActive(unsigned long MSec = 0xFFFFFFFF);
};
//#####################################################################################
//#####################################################################################

//#####################################################################################
//#include "MMutex.h"
//#####################################################################################
//BEGIN_LMYUNIT(MCriticalSection,MObject)

//END_LMYUNIT
//#####################################################################################
template <typename T> MCriticalSection<T>::MLock::MLock(MCriticalSection& section )
						:m_section( section ) 
{
	m_section.Lock();
}
//#####################################################################################
 template <typename T> MCriticalSection<T>::MLock::~MLock()
{
	m_section.UnLock();
}
//#####################################################################################
 template <typename T>MCriticalSection<T>::MCriticalSection(void)
{
#ifdef WINDOWSCODE
	::InitializeCriticalSection(&m_Section);
#else	
	pthread_mutex_init(&m_Section,NULL);
	m_LastThreadId = (unsigned long)(-1);
	m_nLockCount = 0;
#endif
}
//#####################################################################################
 template <typename T>MCriticalSection<T>::~MCriticalSection()
{
#ifdef WINDOWSCODE
	::DeleteCriticalSection(&m_Section);
#else
	pthread_mutex_destroy(&m_Section);
	m_LastThreadId = (unsigned long)(-1);
#endif
}
//#####################################################################################
 template <typename T>void MCriticalSection<T>::Lock(void)
{
#ifdef WINDOWSCODE
	::EnterCriticalSection(&m_Section);
#else
	unsigned long			errorcode;
	errorcode = (unsigned long)pthread_self();
	// ������Ǳ��߳�ǰ��������
	// ��ȴ�ֱ������
	// �жϵ�ͬʱ, m_curLockThread���ܱ������̸߳ı�
	// �������߳�һ�����Ὣm_curLockThread�ı���뱾�߳���ͬ�ı�ʶ
	// ���Ҹñ�ʶ��һ������, ��һ������ָ������ɸı�, �������븱���Ĳ�ͬ
	if ( m_LastThreadId != errorcode )
	{
		//����ͬһ���߳�
		pthread_mutex_lock(&m_Section);

	}
	m_nLockCount++;
	m_LastThreadId = errorcode;
#endif
}
//#####################################################################################
 template <typename T> void MCriticalSection<T>::UnLock(void)
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
//#####################################################################################
 template <typename T> MLocalSection<T>::MLocalSection(void)
{
	m_SectionPtr = NULL;
}
//#####################################################################################
 template <typename T> MLocalSection<T>::~MLocalSection()
{
	UnLock();
}
//#####################################################################################
 template <typename T> void MLocalSection<T>::AttchLock(MCriticalSection<T> * In)
{
	m_SectionPtr = In;
	if ( m_SectionPtr != NULL )
	{
		m_SectionPtr->Lock();
	}
}
//#####################################################################################
 template <typename T> void MLocalSection<T>::UnLock(void)
{
	if ( m_SectionPtr != NULL )
	{
		m_SectionPtr->UnLock();
		m_SectionPtr = NULL;
	}
}
//#####################################################################################
//BEGIN_LMYUNIT(MMrSwSection,MObject)

//	ERROR_DEFINE(ERROR_MMRSWSECTION_READFAL,"MMrSwSection","�����ٽ���������ʧ��[�ȴ���ʱ]")
//	ERROR_DEFINE(ERROR_MMRSWSECTION_WRITEFAL,"MMrSwSection","�����ٽ���д����ʧ��[�ȴ���ʱ]")

//END_LMYUNIT
//#####################################################################################
 template <typename T> MMrSwSection<T>::MRLock::MRLock(MMrSwSection& section, int& nRlt,  unsigned short nTry ) 
					:m_section( section )
{
	m_bLocked = ((nRlt = m_section.LockRead( nTry )) > 0); 
}
//#####################################################################################
 template <typename T> MMrSwSection<T>::MRLock::~MRLock()
{ 
	if( m_bLocked ) m_section.UnLock(); 
}
//#####################################################################################
 template <typename T> MMrSwSection<T>::MWLock::MWLock( MMrSwSection& section, int& nRlt,  unsigned short nTry )
					:m_section( section )
{	
	m_bLocked = ((nRlt = m_section.LockWrite( nTry )) >0); 
}
//#####################################################################################
 template <typename T> MMrSwSection<T>::MWLock::~MWLock()
{ 
	if( m_bLocked ) m_section.UnLock(); 
}

//#####################################################################################
 template <typename T> MMrSwSection<T>::MMrSwSection(void)
{
#ifdef WINDOWSCODE
	::InitializeCriticalSection(&m_Section);
#else
	pthread_mutex_init(&m_Section,NULL);
#endif
	m_Active = 0;
	m_WaitWriteCount = 0;
}
//#####################################################################################
 template <typename T> MMrSwSection<T>::~MMrSwSection()
{
#ifdef WINDOWSCODE
	::DeleteCriticalSection(&m_Section);
#else
	pthread_mutex_destroy(&m_Section);
#endif
}
//#####################################################################################
 template <typename T>int  MMrSwSection<T>::LockRead(unsigned short TryTime)
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
		//		return(ERROR_MMRSWSECTION_READFAL);
				return -1;
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
				//return(ERROR_MMRSWSECTION_READFAL);
				return -1;
			}
		}

		usleep(50000);
	}
#endif
}
//#####################################################################################
 template <typename T> int  MMrSwSection<T>::LockWrite(unsigned short TryTime)
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
//				return(ERROR_MMRSWSECTION_WRITEFAL);
				return -1;
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
				//return(ERROR_MMRSWSECTION_WRITEFAL);
				return 1;
			}
		}

		usleep(50000);
	}
#endif
}
//#####################################################################################
 template <typename T> void MMrSwSection<T>::UnLock(void)
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
//#####################################################################################
 template <typename T> MLocalComplexSection<T>::MLocalComplexSection(void)
{
	m_Section = NULL;
}
//#####################################################################################
 template <typename T> MLocalComplexSection<T>::~MLocalComplexSection()
{
	UnAttch();
}
//#####################################################################################
 template <typename T> int  MLocalComplexSection<T>::AttchLockRead(MComplexMrSwSection<T> * section,unsigned long TimeOut)
{
	m_Section = section;
	return(m_Section->LockRead(TimeOut));
}
//#####################################################################################
 template <typename T> int  MLocalComplexSection<T>::AttchLockWrite(MComplexMrSwSection<T> * section,unsigned long TimeOut)
{
	m_Section = section;
	return(m_Section->LockWrite(TimeOut));
}
//#####################################################################################
 template <typename T> void MLocalComplexSection<T>::UnAttch(void)
{
	if ( m_Section != NULL )
	{
		m_Section->UnLock();
		m_Section = NULL;
	}
}
//#####################################################################################
//BEGIN_LMYUNIT(MComplexMrSwSection,MObject)

//	ERROR_DEFINE(ERROR_MCOMPLEXMRSWSECTION_READFAL,"MComplexMrSwSection","�����ٽ���������ʧ��[�ȴ���ʱ]")
//	ERROR_DEFINE(ERROR_MCOMPLEXMRSWSECTION_WRITEFAL,"MComplexMrSwSection","�����ٽ���д����ʧ��[�ȴ���ʱ]")

//END_LMYUNIT
//#####################################################################################
 template <typename T> MComplexMrSwSection<T>::MRLock::MRLock(MComplexMrSwSection& section, int& nRlt, unsigned long nTO ) 
					:m_section( section )
{
	m_bLocked = ( (nRlt = m_section.LockRead( nTO )) > 0 ); 
}
//#####################################################################################
 template <typename T> MComplexMrSwSection<T>::MRLock::~MRLock()
{ 
	if( m_bLocked ) m_section.UnLock(); 
}
//#####################################################################################
 template <typename T> MComplexMrSwSection<T>::MWLock::MWLock( MComplexMrSwSection& section, int& nRlt, unsigned long nTO )
					:m_section( section )
{	
	m_bLocked = ( (nRlt = m_section.LockWrite( nTO )) > 0 ); 
}
//#####################################################################################
 template <typename T>MComplexMrSwSection<T>::MWLock::~MWLock()
{ 
	if( m_bLocked ) m_section.UnLock(); 
}
//#####################################################################################
 template <typename T> MComplexMrSwSection<T>::MComplexMrSwSection(void)
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
//#####################################################################################
 template <typename T> MComplexMrSwSection<T>::~MComplexMrSwSection()
{
#ifdef WINDOWSCODE
	::DeleteCriticalSection(&m_Section);
	::CloseHandle(m_WaitReadSem);
	::CloseHandle(m_WaitWriteSem);
#else
	pthread_rwlock_destroy(&m_Section);
#endif
}
//#####################################################################################
 template <typename T> int  MComplexMrSwSection<T>::LockRead(unsigned long TimeOut)
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
//			return(ERROR_MCOMPLEXMRSWSECTION_READFAL);
			return -1;
		}
	}

	return(1);
#else
	return ( (pthread_rwlock_rdlock(&m_Section) == 0) ? 1 : -1 );
#endif
}
//#####################################################################################
 template <typename T> int  MComplexMrSwSection<T>::LockWrite(unsigned long TimeOut)
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
//			return(ERROR_MCOMPLEXMRSWSECTION_WRITEFAL);
			return -1;
		}
	}

	return(1);
#else
	return ( (pthread_rwlock_wrlock(&m_Section)== 0) ? 1 : -1 );
#endif
}
//#####################################################################################
 template <typename T> void MComplexMrSwSection<T>::UnLock(void)
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
 template <typename T> MSemaphore<T>::MLock::MLock( MSemaphore& sem, bool& rlt, unsigned long lTimeOut ):m_sem( sem )
{
	m_bLocked = rlt = m_sem.Lock( lTimeOut );
}
//#####################################################################################
 template <typename T> MSemaphore<T>::MLock::~MLock()
{
	if( m_bLocked ) m_sem.UnLock();
}
//#####################################################################################
 template <typename T> MSemaphore<T>::MSemaphore( void )
{
#ifdef WINDOWSCODE
	 m_hSem = NULL;
#else
#endif //WINDOWSCODE
}
//#####################################################################################
 template <typename T> MSemaphore<T>::~MSemaphore( void )
{
#ifdef WINDOWSCODE
	if( m_hSem )
		::CloseHandle( m_hSem );
	m_hSem = NULL;
#else
#endif //WINDOWSCODE
}
//#####################################################################################
 template <typename T> int	 MSemaphore<T>::Instance( long lInitialCount, long lMaxCount )
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
//#####################################################################################
 template <typename T> bool MSemaphore<T>::Lock( unsigned long lTimeOut )
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
//#####################################################################################
 template <typename T> void MSemaphore<T>::UnLock( long lCount )
{
#ifdef WINDOWSCODE
	::ReleaseSemaphore( m_hSem, lCount, NULL );
#else
	return;
#endif //WINDOWSCODE
}
//#####################################################################################
 template <typename T> MWaitEvent<T>::MWaitEvent(void)
{
#ifdef WINDOWSCODE
	m_Handle = NULL;
#else
	pthread_cond_init(&m_Handle,NULL);
	pthread_mutex_init(&m_Section,NULL);
#endif
}
//#####################################################################################
 template <typename T> MWaitEvent<T>::~MWaitEvent()
{
#ifdef WINDOWSCODE
	Release();
#else
	pthread_cond_destroy(&m_Handle);
	pthread_mutex_destroy(&m_Section);
#endif
}
//#####################################################################################
 template <typename T> int  MWaitEvent<T>::Instance(void)
{
#ifdef WINDOWSCODE
	Release();
	
	if ( (m_Handle = ::CreateEvent(NULL,FALSE,FALSE,NULL)) == NULL )
	{
//		return(ERROR_SYSTEM(GetLastError()));
		return -2;
	}
#else
#endif
	
	return(1);
}
//#####################################################################################
 template <typename T> void MWaitEvent<T>::Release(void)
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
//#####################################################################################
 template <typename T> void MWaitEvent<T>::ActiveEvent(void)
{
#ifdef WINDOWSCODE
	::SetEvent(m_Handle);
#else
	pthread_cond_signal(&m_Handle);
#endif
}
//#####################################################################################
 template <typename T> int  MWaitEvent<T>::WaitUntilActive(unsigned long MSec)
{
	register int				errorcode;
#ifdef WINDOWSCODE
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
	//�������ֻ�ܵȴ���ȷ�����ʱ��
	temptime.tv_sec = ::time(NULL) + max( 1, (int )(MSec/1000) );
	temptime.tv_nsec = 0;
	//temptime = MSec;
	errorcode = pthread_cond_timedwait(&m_Handle, &m_Section, &temptime);
	if ( errorcode != 0 )
	{
		return (errorcode);
	}
	else
	{
		return (1);
	}
#endif
}
//#####################################################################################
#endif
