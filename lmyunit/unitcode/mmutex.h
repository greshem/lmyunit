//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMMutexH__
#define __LmyUnitMMutexH__
//--------------------------------------------------------------------------------------------------------------------------------
//����ͷ�ļ�
#include "mobject.h"
//................................................................................................................................
#ifdef WINDOWSCODE
//................................................................................................................................
//Windows����ϵͳ
//................................................................................................................................
#else
//................................................................................................................................
//Linux����ϵͳ
#include <pthread.h>
//................................................................................................................................
#endif
//--------------------------------------------------------------------------------------------------------------------------------
class MCriticalSection : public MObject
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

	DECLARE_LMYUNIT(MCriticalSection)
};
//--------------------------------------------------------------------------------------------------------------------------------
class MLocalSection
{
protected:
	MCriticalSection			*		m_SectionPtr;
public:
	MLocalSection(void);
	virtual ~MLocalSection();
public:
	void AttchLock(MCriticalSection * In);
	void UnLock(void);
};
//--------------------------------------------------------------------------------------------------------------------------------
#define		ERROR_MMRSWSECTION_READFAL		ERROR_USER(10)			//�����ٽ���������ʧ��[�ȴ���ʱ]
#define		ERROR_MMRSWSECTION_WRITEFAL		ERROR_USER(11)			//�����ٽ���д����ʧ��[�ȴ���ʱ]
//................................................................................................................................
class MMrSwSection : public MObject
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

	DECLARE_LMYUNIT(MMrSwSection)
};
//--------------------------------------------------------------------------------------------------------------------------------
#define		ERROR_MCOMPLEXMRSWSECTION_READFAL		ERROR_USER(12)			//�����ٽ���������ʧ��[�ȴ���ʱ]
#define		ERROR_MCOMPLEXMRSWSECTION_WRITEFAL		ERROR_USER(13)			//�����ٽ���д����ʧ��[�ȴ���ʱ]
//................................................................................................................................
class MComplexMrSwSection : public MObject
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

	DECLARE_LMYUNIT(MComplexMrSwSection)
};

//--------------------------------------------------------------------------------------------------------------------------------
class MLocalComplexSection
{
protected:
	MComplexMrSwSection			*	m_Section;
public:
	MLocalComplexSection(void);
	virtual ~MLocalComplexSection();
public:
	int  AttchLockRead(MComplexMrSwSection * section,unsigned long TimeOut = 5000);
	int  AttchLockWrite(MComplexMrSwSection * section,unsigned long TimeOut = 0xFFFFFFFF);
	void UnAttch(void);
};

//--------------------------------------------------------------------------------------------------------------------------------
//========================================================================
//************************************************************************
//========================================================================

class MSemaphore : public MObject
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
//--------------------------------------------------------------------------------------------------------------------------------
//�ȴ��¼�����Ȼ�������ڶ�����̣���������¼����ƣ�����Ϊ�˼���Linux��������Ҫ���ڽ����ڲ������̼�ʹ�õ�����պ������
//��Ҫ������ͷǼ���������������sleep���������ܹ�������Ӧ��
class MWaitEvent
{
protected:
#ifdef WINDOWSCODE
	HANDLE									m_Handle;
#else
	pthread_cond_t							m_Handle;
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
//--------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------

