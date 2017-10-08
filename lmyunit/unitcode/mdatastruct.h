//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMDataStructH__
#define __LmyUnitMDataStructH__
//--------------------------------------------------------------------------------------------------------------------------------
//公共头文件
#include "mobject.h"
#include "mmutex.h"
//................................................................................................................................
#ifdef WINDOWSCODE
//................................................................................................................................
//Windows操作系统
//................................................................................................................................
#else
//................................................................................................................................
//Linux操作系统
//................................................................................................................................
#endif
//--------------------------------------------------------------------------------------------------------------------------------
//通用循环队列，不支持多线程
template<class templateRecord>class MLoopGroupSt
{
protected:
	templateRecord				*	m_RecordData;
	unsigned short					m_MaxRecord;
	unsigned short					m_HeadPtr;
	unsigned short					m_TailPtr;
public:
	MLoopGroupSt(void);
	virtual ~MLoopGroupSt();
public:
	int  Instance(unsigned short MaxRecord);
	void Release(void);
public:
	int  PutData(templateRecord * In);
	int  GetData(templateRecord * Out);
public:
	void Clear(void);
public:
	bool IsEmpty(void);
	bool IsFull(void);
public:
	unsigned short GetCount(void);
};
//--------------------------------------------------------------------------------------------------------------------------------
//通用循环队列，支持多线程
template<class templateRecord>class MLoopGroupMt : public MLoopGroupSt<templateRecord>
{
protected:
	MCriticalSection				m_Section;
public:
	MLoopGroupMt(void);
	virtual ~MLoopGroupMt();
public:
	int  Instance(unsigned short MaxRecord);
	void Release(void);
public:
	int  PutData(templateRecord * In);
	int  GetData(templateRecord * Out);
public:
	void Clear(void);
public:
	bool IsEmpty(void);
	bool IsFull(void);
public:
	unsigned short GetCount(void);
};
//--------------------------------------------------------------------------------------------------------------------------------
#define		ERROR_MRESOURCERECORDST_NOMEMORY		ERROR_USER(40)		//没有足够的内存可以分配
#define		ERROR_MRESOURCERECORDST_FULL			ERROR_USER(41)		//资源队列已满，不能加入其他资源
#define		ERROR_MRESOURCERECORDST_EMPTY			ERROR_USER(42)		//没有任何可用资源可以分配
//................................................................................................................................
//资源使用纪录，不支持多线程
class MResourceRecordSt : public MObject
{
protected:
	unsigned short				*	m_RecordData;
	unsigned short					m_MaxRecord;
	unsigned short					m_HeadPtr;
	unsigned short					m_TailPtr;
public:
	MResourceRecordSt(void);
	virtual ~MResourceRecordSt();
public:
	int  Instance(unsigned short MaxCount);
	void Release(void);
public:
	int  GetResource(void);
	int  PutResource(unsigned short ResourceID);

	DECLARE_LMYUNIT(MResourceRecordSt)
};
//--------------------------------------------------------------------------------------------------------------------------------
//资源使用纪录，支持多线程
class MResourceRecordMt : public MResourceRecordSt
{
protected:
	MCriticalSection				m_Section;
public:
	MResourceRecordMt(void);
	virtual ~MResourceRecordMt();
public:
	int  Instance(unsigned short MaxCount);
	void Release(void);
public:
	int  GetResource(void);
	int  PutResource(unsigned short ResourceID);

	DECLARE_LMYUNIT(MResourceRecordMt)
};
//--------------------------------------------------------------------------------------------------------------------------------
#define		ERROR_MCHARLOOPGROUPST_NOMEMORY		ERROR_USER(50)		//没有足够的内存可以分配
#define		ERROR_MCHARLOOPGROUPST_FULL			ERROR_USER(51)		//队列已满，不能加入其他数据
#define		ERROR_MCHARLOOPGROUPST_EMPTY		ERROR_USER(52)		//队列为空，不能获取任何数据
//................................................................................................................................
//字符循环缓冲队列，不支持多线程
class MCharLoopGroupSt : public MObject
{
protected:
	char					*	m_RecordData;
	unsigned short				m_MaxRecord;
	unsigned short				m_HeadPtr;
	unsigned short				m_TailPtr;
public:
	MCharLoopGroupSt(void);
	virtual ~MCharLoopGroupSt();
public:
	int  Instance(unsigned short MaxCount);
	void Release(void);
public:
	int  PutData(char * InBuf,unsigned short InSize);
	int  GetData(char * OutBuf,unsigned short InSize);
public:
	bool IsEmpty(void);
public:
	void Clear(void);

	DECLARE_LMYUNIT(MCharLoopGroupSt)
};
//--------------------------------------------------------------------------------------------------------------------------------
//字符循环缓冲队列，支持多线程
class MCharLoopGroupMt : public MCharLoopGroupSt
{
protected:
	MCriticalSection			m_Section;
public:
	MCharLoopGroupMt(void);
	virtual ~MCharLoopGroupMt();
public:
	int  Instance(unsigned short MaxCount);
	void Release(void);
public:
	int  PutData(char * InBuf,unsigned short InSize);
	int  GetData(char * OutBuf,unsigned short InSize);
public:
	void Clear(void);

	DECLARE_LMYUNIT(MCharLoopGroupMt)
};
//--------------------------------------------------------------------------------------------------------------------------------
//哈西表，不支持多线程
template<class templateRecord>class MHashTableSt
{
#pragma pack(1)
	typedef struct
	{
		templateRecord			Index;
		unsigned long			AddtionData;
		bool					UserFlag;
	} tagHashTableNodeInfo;
#pragma pack()
protected:
	tagHashTableNodeInfo	*	m_RecordData;
	unsigned short				m_MaxRecord;
	unsigned short				m_RecordCount;
public:
	MHashTableSt(void);
	virtual ~MHashTableSt();
public:
	int  Instance(unsigned short MaxRecord);
	void Release(void);
public:
	int  PutData(unsigned short FindCode,templateRecord Index,unsigned long AddtionData);
	int  FindData(unsigned short FindCode,templateRecord Index);
	int  DeleteData(unsigned short FindCode,templateRecord Index);
};
//--------------------------------------------------------------------------------------------------------------------------------
//哈西表，支持多线程
template<class templateRecord>class MHashTableMt : public MHashTableSt<templateRecord>
{
protected:
	MCriticalSection			m_Section;
public:
	MHashTableMt(void);
	virtual ~MHashTableMt();
public:
	int  Instance(unsigned short MaxRecord);
	void Release(void);
public:
	int  PutData(unsigned short FindCode,templateRecord Index,unsigned long AddtionData);
	int  FindData(unsigned short FindCode,templateRecord Index);
	int  DeleteData(unsigned short FindCode,templateRecord Index);
};
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//模版类的实现
template<class templateRecord> MLoopGroupSt<templateRecord>::MLoopGroupSt(void)
{
	m_RecordData = NULL;
	m_MaxRecord = 0;
	m_HeadPtr = 0;
	m_TailPtr = 0;
}
//................................................................................................................................
template<class templateRecord> MLoopGroupSt<templateRecord>::~MLoopGroupSt()
{
	Release();
}
//................................................................................................................................
template<class templateRecord> int  MLoopGroupSt<templateRecord>::Instance(unsigned short MaxRecord)
{
	Release();

	m_RecordData = new templateRecord[MaxRecord];
	if ( m_RecordData == NULL )
	{
		return(ERROR_MLOOPGROUPST_NOMEMORY);
	}

	m_MaxRecord = MaxRecord;
	m_HeadPtr = 0;
	m_TailPtr = 0;

	return(1);
}
//................................................................................................................................
template<class templateRecord> void MLoopGroupSt<templateRecord>::Release(void)
{
	if ( m_RecordData != NULL )
	{
		delete [] m_RecordData;
		m_RecordData = NULL;
	}
	m_MaxRecord = 0;
	m_HeadPtr = 0;
	m_TailPtr = 0;
}
//................................................................................................................................
template<class templateRecord> int  MLoopGroupSt<templateRecord>::PutData(templateRecord * In)
{
	register unsigned short					errorcode;

	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);
	assert(In != NULL);

	errorcode = (m_TailPtr + 1) % m_MaxRecord;
	if ( errorcode == m_HeadPtr )
	{
		return(ERROR_MLOOPGROUPST_FULL);
	}

	memcpy((char *)&m_RecordData[m_TailPtr],(char *)In,sizeof(templateRecord));
	m_TailPtr = errorcode;

	return(1);
}
//................................................................................................................................
template<class templateRecord> int  MLoopGroupSt<templateRecord>::GetData(templateRecord * Out)
{
	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);
	assert(Out != NULL);

	if ( m_HeadPtr == m_TailPtr )
	{
		return(ERROR_MLOOPGROUPST_EMPTY);
	}

	memcpy((char *)Out,(char *)&m_RecordData[m_HeadPtr],sizeof(templateRecord));
	m_HeadPtr = (m_HeadPtr + 1) % m_MaxRecord;

	return(1);
}
//................................................................................................................................
template<class templateRecord> void MLoopGroupSt<templateRecord>::Clear(void)
{
	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);

	m_TailPtr = m_HeadPtr;
}
//................................................................................................................................
template<class templateRecord> bool MLoopGroupSt<templateRecord>::IsEmpty(void)
{
	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);

	if ( m_HeadPtr == m_TailPtr )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//................................................................................................................................
template<class templateRecord> bool MLoopGroupSt<templateRecord>::IsFull(void)
{
	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);

	if ( (m_TailPtr + 1) % m_MaxRecord == m_HeadPtr )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//................................................................................................................................
template<class templateRecord> unsigned short MLoopGroupSt<templateRecord>::GetCount(void)
{
	return((m_TailPtr + m_MaxRecord - m_HeadPtr) % m_MaxRecord);
}
//--------------------------------------------------------------------------------------------------------------------------------
template<class templateRecord> MLoopGroupMt<templateRecord>::MLoopGroupMt(void)
{
	
}
//................................................................................................................................
template<class templateRecord> MLoopGroupMt<templateRecord>::~MLoopGroupMt()
{
	Release();
}
//................................................................................................................................
template<class templateRecord> int  MLoopGroupMt<templateRecord>::Instance(unsigned short MaxRecord)
{
	register int					errorcode;

	m_Section.Lock();

	errorcode = MLoopGroupSt<templateRecord>::Instance(MaxRecord);

	m_Section.UnLock();

	return(errorcode);
}
//................................................................................................................................
template<class templateRecord> void MLoopGroupMt<templateRecord>::Release(void)
{
	m_Section.Lock();

	MLoopGroupSt<templateRecord>::Release();

	m_Section.UnLock();
}
//................................................................................................................................
template<class templateRecord> int  MLoopGroupMt<templateRecord>::PutData(templateRecord * In)
{
	register int					errorcode;

	m_Section.Lock();

	errorcode = MLoopGroupSt<templateRecord>::PutData(In);

	m_Section.UnLock();

	return(errorcode);
}
//................................................................................................................................
template<class templateRecord> int  MLoopGroupMt<templateRecord>::GetData(templateRecord * Out)
{
	register int					errorcode;

	m_Section.Lock();

	errorcode = MLoopGroupSt<templateRecord>::GetData(Out);

	m_Section.UnLock();

	return(errorcode);
}
//................................................................................................................................
template<class templateRecord> void MLoopGroupMt<templateRecord>::Clear(void)
{
	m_Section.Lock();

	MLoopGroupSt<templateRecord>::Clear();

	m_Section.UnLock();
}
//................................................................................................................................
template<class templateRecord> bool MLoopGroupMt<templateRecord>::IsEmpty(void)
{
	register bool					errorcode;

	m_Section.Lock();

	errorcode = MLoopGroupSt<templateRecord>::IsEmpty();

	m_Section.UnLock();

	return(errorcode);
}
//................................................................................................................................
template<class templateRecord> bool MLoopGroupMt<templateRecord>::IsFull(void)
{
	register bool					errorcode;

	m_Section.Lock();

	errorcode = MLoopGroupSt<templateRecord>::IsFull();

	m_Section.UnLock();

	return(errorcode);
}
//................................................................................................................................
template<class templateRecord> unsigned short MLoopGroupMt<templateRecord>::GetCount(void)
{
	register unsigned short			errorcode;

	m_Section.Lock();

	errorcode = MLoopGroupSt<templateRecord>::GetCount();

	m_Section.UnLock();

	return(errorcode);
}
//--------------------------------------------------------------------------------------------------------------------------------
template<class templateRecord> MHashTableSt<templateRecord>::MHashTableSt(void)
{
	m_RecordData = NULL;
	m_MaxRecord = 0;
	m_RecordCount = 0;
}
//................................................................................................................................
template<class templateRecord> MHashTableSt<templateRecord>::~MHashTableSt()
{
	Release();
}
//................................................................................................................................
template<class templateRecord> int  MHashTableSt<templateRecord>::Instance(unsigned short MaxRecord)
{
	register int						i;

	Release();

	m_RecordData = new tagHashTableNodeInfo[MaxRecord];
	if ( m_RecordData == NULL )
	{
		return(ERROR_MHASHTABLEST_NOMEMORY);
	}

	m_MaxRecord = MaxRecord;
	m_RecordCount = 0;

	for ( i=0;i<=m_MaxRecord-1;i++ )
	{
		m_RecordData[i].UserFlag = false;
	}

	return(1);
}
//................................................................................................................................
template<class templateRecord> void MHashTableSt<templateRecord>::Release(void)
{
	if ( m_RecordData != NULL )
	{
		delete [] m_RecordData;
		m_RecordData = NULL;
	}
	m_MaxRecord = 0;
	m_RecordCount = 0;
}
//................................................................................................................................
template<class templateRecord> int  MHashTableSt<templateRecord>::PutData(unsigned short FindCode,templateRecord Index,unsigned long AddtionData)
{
	register unsigned short			offset;
	register unsigned short			firstoffset;

	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);

	if ( m_RecordCount >= m_MaxRecord )
	{
		return(ERROR_MHASHTABLEST_FULL);
	}

	firstoffset = FindCode % m_MaxRecord;
	offset = firstoffset;

	while ( 1 )
	{
		if ( m_RecordData[offset].UserFlag == false )
		{
			m_RecordData[offset].UserFlag = true;
			memcpy((char *)&m_RecordData[offset].Index,(char *)&Index,sizeof(templateRecord));
			m_RecordData[offset].AddtionData = AddtionData;

			m_RecordCount ++;

			return(offset);
		}
		else
		{
			offset = (offset + FindCode) % m_MaxRecord;
			if ( offset = firstoffset )
			{
				return(ERROR_MHASHTABLEST_FULL);
			}
		}
	}
}
//................................................................................................................................
template<class templateRecord> int  MHashTableSt<templateRecord>::FindData(unsigned short FindCode,templateRecord Index)
{
	register unsigned short			offset;
	register unsigned short			firstoffset;

	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);

	if ( m_RecordCount == 0 )
	{
		return(ERROR_MHASHTABLEST_EMPTY);
	}

	firstoffset = FindCode % m_MaxRecord;
	offset = firstoffset;

	while ( 1 )
	{
		if (	m_RecordData[offset].UserFlag == true && 
				memcmp((char *)&m_RecordData[offset].Index,(char *)&Index,sizeof(templateRecord)) == 0 )
		{
			return(m_RecordData[offset].AddtionData);
		}
		else
		{
			offset = (offset + FindCode) % m_MaxRecord;
			if ( offset = firstoffset )
			{
				return(ERROR_MHASHTABLEST_NODATA);
			}
		}
	}
}
//................................................................................................................................
template<class templateRecord> int  MHashTableSt<templateRecord>::DeleteData(unsigned short FindCode,templateRecord Index)
{
	register unsigned short			offset;
	register unsigned short			firstoffset;

	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);

	if ( m_RecordCount == 0 )
	{
		return(ERROR_MHASHTABLEST_EMPTY);
	}

	firstoffset = FindCode % m_MaxRecord;
	offset = firstoffset;

	while ( 1 )
	{
		if (	m_RecordData[offset].UserFlag == true && 
				memcmp((char *)&m_RecordData[offset].Index,(char *)&Index,sizeof(templateRecord)) == 0 )
		{
			m_RecordCount --;
			m_RecordData[offset].UserFlag = false;
			return(m_RecordData[offset].AddtionData);
		}
		else
		{
			offset = (offset + FindCode) % m_MaxRecord;
			if ( offset = firstoffset )
			{
				return(ERROR_MHASHTABLEST_NODATA);
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
template<class templateRecord> MHashTableMt<templateRecord>::MHashTableMt(void)
{

}
//................................................................................................................................
template<class templateRecord> MHashTableMt<templateRecord>::~MHashTableMt()
{
	Release();
}
//................................................................................................................................
template<class templateRecord> int  MHashTableMt<templateRecord>::Instance(unsigned short MaxRecord)
{
	register int						errorcode;

	m_Section.Lock();

	errorcode = MHashTableSt<templateRecord>::Instance(MaxRecord);

	m_Section.UnLock();

	return(errorcode);
}
//................................................................................................................................
template<class templateRecord> void MHashTableMt<templateRecord>::Release(void)
{
	m_Section.Lock();

	MHashTableSt<templateRecord>::Release();

	m_Section.UnLock();
}
//................................................................................................................................
template<class templateRecord> int  MHashTableMt<templateRecord>::PutData(unsigned short FindCode,templateRecord Index,unsigned long AddtionData)
{
	register int						errorcode;

	m_Section.Lock();

	errorcode = MHashTableSt<templateRecord>::PutData(FindCode,Index,AddtionData);

	m_Section.UnLock();

	return(errorcode);
}
//................................................................................................................................
template<class templateRecord> int  MHashTableMt<templateRecord>::FindData(unsigned short FindCode,templateRecord Index)
{
	register int						errorcode;

	m_Section.Lock();

	errorcode = MHashTableSt<templateRecord>::FindData(FindCode,Index);

	m_Section.UnLock();

	return(errorcode);
}
//................................................................................................................................
template<class templateRecord> int  MHashTableMt<templateRecord>::DeleteData(unsigned short FindCode,templateRecord Index)
{
	register int						errorcode;

	m_Section.Lock();

	errorcode = MHashTableSt<templateRecord>::DeleteData(FindCode,Index);

	m_Section.UnLock();

	return(errorcode);
}
//--------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------
