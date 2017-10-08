//#####################################################################################
//#####################################################################################
#ifndef __LmyUnitMDataStructH__
#define __LmyUnitMDataStructH__
//#####################################################################################
//公共头文件
//#include "MObject.h"
#include "MString.hpp"
#include "MMutex.hpp"
//#####################################################################################
#ifdef WINDOWSCODE
//#####################################################################################
//Windows操作系统
//#####################################################################################
#else
//#####################################################################################
//Linux操作系统
//#####################################################################################
#endif
//#####################################################################################
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
//#####################################################################################
//通用循环队列，支持多线程
template<class templateRecord>class MLoopGroupMt : public MLoopGroupSt<templateRecord>
{
protected:
	MCriticalSection<char>				m_Section;
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
//#####################################################################################
#define		ERROR_MRESOURCERECORDST_NOMEMORY		ERROR_USER(40)		//没有足够的内存可以分配
#define		ERROR_MRESOURCERECORDST_FULL			ERROR_USER(41)		//资源队列已满，不能加入其他资源
#define		ERROR_MRESOURCERECORDST_EMPTY			ERROR_USER(42)		//没有任何可用资源可以分配
//#####################################################################################
//资源使用纪录，不支持多线程
template <typename T >class MResourceRecordSt //: public MObject
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

//	DECLARE_LMYUNIT(MResourceRecordSt)
};
//#####################################################################################
//资源使用纪录，支持多线程
template <typename T> class MResourceRecordMt : public MResourceRecordSt<T>
{
protected:
	MCriticalSection<char>			m_Section;
public:
	MResourceRecordMt(void);
	virtual ~MResourceRecordMt();
public:
	int  Instance(unsigned short MaxCount);
	void Release(void);
public:
	int  GetResource(void);
	int  PutResource(unsigned short ResourceID);

//	DECLARE_LMYUNIT(MResourceRecordMt)
};
//#####################################################################################
#define		ERROR_MCHARLOOPGROUPST_NOMEMORY		ERROR_USER(50)		//没有足够的内存可以分配
#define		ERROR_MCHARLOOPGROUPST_FULL			ERROR_USER(51)		//队列已满，不能加入其他数据
#define		ERROR_MCHARLOOPGROUPST_EMPTY		ERROR_USER(52)		//队列为空，不能获取任何数据
//#####################################################################################
//字符循环缓冲队列，不支持多线程
template <typename T> class MCharLoopGroupSt //: public MObject
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

//	DECLARE_LMYUNIT(MCharLoopGroupSt)
};
//#####################################################################################
//字符循环缓冲队列，支持多线程
template <typename T> class MCharLoopGroupMt : public MCharLoopGroupSt<T>
{
protected:
	MCriticalSection<char>		m_Section;
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

//	DECLARE_LMYUNIT(MCharLoopGroupMt)
};
//#####################################################################################
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
//#####################################################################################
//哈西表，支持多线程
template<class templateRecord>class MHashTableMt : public MHashTableSt<templateRecord>
{
protected:
	MCriticalSection<char>			m_Section;
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
//#####################################################################################
//#####################################################################################
//模版类的实现
template<class templateRecord> MLoopGroupSt<templateRecord>::MLoopGroupSt(void)
{
	m_RecordData = NULL;
	m_MaxRecord = 0;
	m_HeadPtr = 0;
	m_TailPtr = 0;
}
//#####################################################################################
template<class templateRecord> MLoopGroupSt<templateRecord>::~MLoopGroupSt()
{
	Release();
}
//#####################################################################################
template<class templateRecord> int  MLoopGroupSt<templateRecord>::Instance(unsigned short MaxRecord)
{
	Release();

	m_RecordData = new templateRecord[MaxRecord];
	if ( m_RecordData == NULL )
	{
//		return(ERROR_MLOOPGROUPST_NOMEMORY);
				return -1;
	}

	m_MaxRecord = MaxRecord;
	m_HeadPtr = 0;
	m_TailPtr = 0;

	return(1);
}
//#####################################################################################
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
//#####################################################################################
template<typename  templateRecord> int  MLoopGroupSt<templateRecord>::PutData(templateRecord * In)
{
	register unsigned short					errorcode;

	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);
	assert(In != NULL);

	errorcode = (m_TailPtr + 1) % m_MaxRecord;
	if ( errorcode == m_HeadPtr )
	{
//		return(ERROR_MLOOPGROUPST_FULL);
				return -1;
	}

	memcpy((char *)&m_RecordData[m_TailPtr],(char *)In,sizeof(templateRecord));
	m_TailPtr = errorcode;

	return(1);
}
//#####################################################################################
template<typename  templateRecord> int  MLoopGroupSt<templateRecord>::GetData(templateRecord * Out)
{
	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);
	assert(Out != NULL);

	if ( m_HeadPtr == m_TailPtr )
	{
//		return(ERROR_MLOOPGROUPST_EMPTY);
				return -1;
	}

	memcpy((char *)Out,(char *)&m_RecordData[m_HeadPtr],sizeof(templateRecord));
	m_HeadPtr = (m_HeadPtr + 1) % m_MaxRecord;

	return(1);
}
//#####################################################################################
template<typename  templateRecord> void MLoopGroupSt<templateRecord>::Clear(void)
{
	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);

	m_TailPtr = m_HeadPtr;
}
//#####################################################################################
template<typename  templateRecord> bool MLoopGroupSt<templateRecord>::IsEmpty(void)
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
//#####################################################################################
template<typename  templateRecord> bool MLoopGroupSt<templateRecord>::IsFull(void)
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
//#####################################################################################
template<typename templateRecord> unsigned short MLoopGroupSt<templateRecord>::GetCount(void)
{
	return((m_TailPtr + m_MaxRecord - m_HeadPtr) % m_MaxRecord);
}
//#####################################################################################
template<class templateRecord> MLoopGroupMt<templateRecord>::MLoopGroupMt(void)
{
	
}
//#####################################################################################
template<class templateRecord> MLoopGroupMt<templateRecord>::~MLoopGroupMt()
{
	Release();
}
//#####################################################################################
template<class templateRecord> int  MLoopGroupMt<templateRecord>::Instance(unsigned short MaxRecord)
{
	register int					errorcode;

	m_Section.Lock();

	errorcode = MLoopGroupSt<templateRecord>::Instance(MaxRecord);

	m_Section.UnLock();

	return(errorcode);
}
//#####################################################################################
template<typename  templateRecord> void MLoopGroupMt<templateRecord>::Release(void)
{
	m_Section.Lock();

	MLoopGroupSt<templateRecord>::Release();

	m_Section.UnLock();
}
//#####################################################################################
template<typename  templateRecord> int  MLoopGroupMt<templateRecord>::PutData(templateRecord * In)
{
	register int					errorcode;

	m_Section.Lock();

	errorcode = MLoopGroupSt<templateRecord>::PutData(In);

	m_Section.UnLock();

	return(errorcode);
}
//#####################################################################################
template<typename templateRecord> int  MLoopGroupMt<templateRecord>::GetData(templateRecord * Out)
{
	register int					errorcode;

	m_Section.Lock();

	errorcode = MLoopGroupSt<templateRecord>::GetData(Out);

	m_Section.UnLock();

	return(errorcode);
}
//###############################################################################
template<typename  templateRecord> void MLoopGroupMt<templateRecord>::Clear(void)
{
	m_Section.Lock();

	MLoopGroupSt<templateRecord>::Clear();

	m_Section.UnLock();
}
//###############################################################################/
template<class templateRecord> bool MLoopGroupMt<templateRecord>::IsEmpty(void)
{
	register bool					errorcode;

	m_Section.Lock();

	errorcode = MLoopGroupSt<templateRecord>::IsEmpty();

	m_Section.UnLock();

	return(errorcode);
}
//#####################################################################################
template<typename  templateRecord> bool MLoopGroupMt<templateRecord>::IsFull(void)
{
	register bool					errorcode;

	m_Section.Lock();

	errorcode = MLoopGroupSt<templateRecord>::IsFull();

	m_Section.UnLock();

	return(errorcode);
}
//#####################################################################################
template<typename templateRecord> unsigned short MLoopGroupMt<templateRecord>::GetCount(void)
{
	register unsigned short			errorcode;

	m_Section.Lock();

	errorcode = MLoopGroupSt<templateRecord>::GetCount();

	m_Section.UnLock();

	return(errorcode);
}
//#####################################################################################
//############################################################################### 
//#hash  表。 
template<typename templateRecord> MHashTableSt<templateRecord>::MHashTableSt(void)
{
	m_RecordData = NULL;
	m_MaxRecord = 0;
	m_RecordCount = 0;
}
//#####################################################################################
template<class templateRecord> MHashTableSt<templateRecord>::~MHashTableSt()
{
	Release();
}
//#####################################################################################
template<class templateRecord> int  MHashTableSt<templateRecord>::Instance(unsigned short MaxRecord)
{
	register int						i;

	Release();

	m_RecordData = new tagHashTableNodeInfo[MaxRecord];
	if ( m_RecordData == NULL )
	{
	//	return(ERROR_MHASHTABLEST_NOMEMORY);
	   return -1;
	}

	m_MaxRecord = MaxRecord;
	m_RecordCount = 0;

	for ( i=0;i<=m_MaxRecord-1;i++ )
	{
		m_RecordData[i].UserFlag = false;
	}

	return(1);
}
//#####################################################################################
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
//#####################################################################################
template<class templateRecord> int  MHashTableSt<templateRecord>::PutData(unsigned short FindCode,templateRecord Index,unsigned long AddtionData)
{
	register unsigned short			offset;
	register unsigned short			firstoffset;

	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);

	if ( m_RecordCount >= m_MaxRecord )
	{
	//	return(ERROR_MHASHTABLEST_FULL);
	   return -1;
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
				//return(ERROR_MHASHTABLEST_FULL);
				return -1;
			}
		}
	}
}
//#####################################################################################
template<class templateRecord> int  MHashTableSt<templateRecord>::FindData(unsigned short FindCode,templateRecord Index)
{
	register unsigned short			offset;
	register unsigned short			firstoffset;

	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);

	if ( m_RecordCount == 0 )
	{
	//	return(ERROR_MHASHTABLEST_EMPTY);
	return -1;
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
			//	return(ERROR_MHASHTABLEST_NODATA);
			return -1;
			}
		}
	}
}
//#####################################################################################
template<class templateRecord> int  MHashTableSt<templateRecord>::DeleteData(unsigned short FindCode,templateRecord Index)
{
	register unsigned short			offset;
	register unsigned short			firstoffset;

	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);

	if ( m_RecordCount == 0 )
	{
	//	return(ERROR_MHASHTABLEST_EMPTY);
	    return -1;
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
			//	return(ERROR_MHASHTABLEST_NODATA);
			return -1;
			}
		}
	}
}
//#####################################################################################
template<class templateRecord> MHashTableMt<templateRecord>::MHashTableMt(void)
{

}
//#####################################################################################
template<class templateRecord> MHashTableMt<templateRecord>::~MHashTableMt()
{
	Release();
}
//#####################################################################################
template<class templateRecord> int  MHashTableMt<templateRecord>::Instance(unsigned short MaxRecord)
{
	register int						errorcode;

	m_Section.Lock();

	errorcode = MHashTableSt<templateRecord>::Instance(MaxRecord);

	m_Section.UnLock();

	return(errorcode);
}
//#####################################################################################
template<class templateRecord> void MHashTableMt<templateRecord>::Release(void)
{
	m_Section.Lock();

	MHashTableSt<templateRecord>::Release();

	m_Section.UnLock();
}
//#####################################################################################
template<class templateRecord> int  MHashTableMt<templateRecord>::PutData(unsigned short FindCode,templateRecord Index,unsigned long AddtionData)
{
	register int						errorcode;

	m_Section.Lock();

	errorcode = MHashTableSt<templateRecord>::PutData(FindCode,Index,AddtionData);

	m_Section.UnLock();

	return(errorcode);
}
//#####################################################################################
template<class templateRecord> int  MHashTableMt<templateRecord>::FindData(unsigned short FindCode,templateRecord Index)
{
	register int						errorcode;

	m_Section.Lock();

	errorcode = MHashTableSt<templateRecord>::FindData(FindCode,Index);

	m_Section.UnLock();

	return(errorcode);
}
//#####################################################################################
template<class templateRecord> int  MHashTableMt<templateRecord>::DeleteData(unsigned short FindCode,templateRecord Index)
{
	register int						errorcode;

	m_Section.Lock();

	errorcode = MHashTableSt<templateRecord>::DeleteData(FindCode,Index);

	m_Section.UnLock();

	return(errorcode);
}
//#####################################################################################
//#####################################################################################
//#####################################################################################
//#include "MDataStruct.h"
//#####################################################################################
/*BEGIN_LMYUNIT(MResourceRecordSt,MObject)

	ERROR_DEFINE(ERROR_MRESOURCERECORDST_NOMEMORY,"MResourceRecordSt","没有足够的内存可以分配")
	ERROR_DEFINE(ERROR_MRESOURCERECORDST_FULL,"MResourceRecordSt","资源队列已满，不能加入其他资源")
	ERROR_DEFINE(ERROR_MRESOURCERECORDST_EMPTY,"MResourceRecordSt","没有任何可用资源可以分配")

END_LMYUNITEND_LMYUNIT*/
//#####################################################################################
template <typename T> MResourceRecordSt<T>::MResourceRecordSt(void)
{
	m_RecordData = NULL;
	m_MaxRecord = 0;
	m_TailPtr = 0;
	m_HeadPtr = 0;
}
//#####################################################################################
template <typename T> MResourceRecordSt<T>::~MResourceRecordSt()
{
	Release();
}
//#####################################################################################
 template <typename T> int  MResourceRecordSt<T>::Instance(unsigned short MaxCount)
{
	register int					i;

	Release();

	m_RecordData = new unsigned short[MaxCount + 1];
	if ( m_RecordData == NULL )
	{
	//	return(ERROR_MRESOURCERECORDST_NOMEMORY);
		return -1;
	}

	m_MaxRecord = MaxCount + 1;
	m_HeadPtr = 0;
	m_TailPtr = MaxCount;

	for ( i=0;i<=m_MaxRecord-1;i++ )
	{
		m_RecordData[i] = i;
	}

	return(1);
}
//#####################################################################################
 template <typename T> void MResourceRecordSt<T>::Release(void)
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
//#####################################################################################
 template <typename T> int  MResourceRecordSt<T>::GetResource(void)
{
	register unsigned short			errorcode;

	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);

	if ( m_HeadPtr == m_TailPtr )
	{
//		return(ERROR_MRESOURCERECORDST_EMPTY);
		return -1;
	}

	errorcode = m_RecordData[m_HeadPtr];
	m_HeadPtr = (m_HeadPtr + 1) % m_MaxRecord;

	return(errorcode);
}
//#####################################################################################
 template <typename T> int  MResourceRecordSt<T>::PutResource(unsigned short ResourceID)
{
	register unsigned short			errorcode;

	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);

	errorcode = (m_TailPtr + 1) % m_MaxRecord;
	if ( errorcode == m_HeadPtr )
	{
	//	return(ERROR_MRESOURCERECORDST_FULL);
		return -1;
	}

	m_RecordData[m_TailPtr] = ResourceID;
	m_TailPtr = errorcode;

	return(1);
}
//#####################################################################################
//BEGIN_LMYUNIT(MResourceRecordMt,MResourceRecordSt)

//END_LMYUNITEND_LMYUNIT
//#####################################################################################
 template <typename T> MResourceRecordMt<T>::MResourceRecordMt(void)
{

}
//#####################################################################################
 template <typename T> MResourceRecordMt<T>::~MResourceRecordMt()
{
	Release();
}
//#####################################################################################
 template <typename T> int  MResourceRecordMt<T>::Instance(unsigned short MaxCount)
{
	register int					errorcode;

	m_Section.Lock();

	errorcode = MResourceRecordSt<T>::Instance(MaxCount);

	m_Section.UnLock();

	return(errorcode);
}
//#####################################################################################
 template <typename T> void MResourceRecordMt<T>::Release(void)
{
	m_Section.Lock();

	MResourceRecordSt<T>::Release();

	m_Section.UnLock();
}
//#####################################################################################
 template <typename T> int  MResourceRecordMt<T>::GetResource(void)
{
	register int					errorcode;

	m_Section.Lock();

	errorcode = MResourceRecordSt<T>::GetResource();

	m_Section.UnLock();

	return(errorcode);
}
//#####################################################################################
 template <typename T> int  MResourceRecordMt<T>::PutResource(unsigned short ResourceID)
{
	register int					errorcode;

	m_Section.Lock();

	errorcode = MResourceRecordSt<T>::PutResource(ResourceID);

	m_Section.UnLock();

	return(errorcode);
}
//#####################################################################################
//BEGIN_LMYUNIT(MCharLoopGroupSt,MObject)

//	ERROR_DEFINE(ERROR_MCHARLOOPGROUPST_NOMEMORY,"MCharLoopGroupSt","没有足够的内存可以分配")
//	ERROR_DEFINE(ERROR_MCHARLOOPGROUPST_FULL,"MCharLoopGroupSt","队列已满，不能加入其他数据")
//	ERROR_DEFINE(ERROR_MCHARLOOPGROUPST_EMPTY,"MCharLoopGroupSt","队列为空，不能获取任何数据")

//END_LMYUNITEND_LMYUNIT
//#####################################################################################
 template <typename T> MCharLoopGroupSt<T>::MCharLoopGroupSt(void)
{
	m_RecordData = NULL;
	m_MaxRecord = 0;
	m_HeadPtr = 0;
	m_TailPtr = 0;
}
//#####################################################################################
 template <typename T> MCharLoopGroupSt<T>::~MCharLoopGroupSt()
{
	Release();
}
//#####################################################################################
 template <typename T> int  MCharLoopGroupSt<T>::Instance(unsigned short MaxCount)
{
	Release();

	m_RecordData = new char[MaxCount];
	if ( m_RecordData == NULL )
	{
	//	return(ERROR_MCHARLOOPGROUPST_NOMEMORY);
		return -1;
	}

	m_MaxRecord = MaxCount;
	m_HeadPtr = 0;
	m_TailPtr = 0;

	return(1);
}
//#####################################################################################
 template <typename T> void MCharLoopGroupSt<T>::Release(void)
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
//#####################################################################################
 template <typename T> int  MCharLoopGroupSt<T>::PutData(char * InBuf,unsigned short InSize)
{
	register unsigned short				errorcode;
	register unsigned short				copysize;

	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);
	assert(InBuf != NULL);

	errorcode = (m_HeadPtr + m_MaxRecord - m_TailPtr - 1) % m_MaxRecord;
	if ( InSize > errorcode )
	{
		//return(ERROR_MCHARLOOPGROUPST_FULL);
		return -1;
	}

	copysize = m_MaxRecord - m_TailPtr;
	if ( copysize >= InSize )
	{
		memcpy(&m_RecordData[m_TailPtr],InBuf,InSize);
	}
	else
	{
		memcpy(&m_RecordData[m_TailPtr],InBuf,copysize);
		memcpy(&m_RecordData[0],InBuf + copysize,InSize - copysize);
	}

	m_TailPtr = (m_TailPtr + InSize) % m_MaxRecord;

	return(InSize);
}
//#####################################################################################
 template <typename T> int  MCharLoopGroupSt<T>::GetData(char * OutBuf,unsigned short InSize)
{
	register unsigned short				errorcode;
	register unsigned short				copysize;

	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);
	assert(OutBuf != NULL);

	errorcode = (m_TailPtr + m_MaxRecord - m_HeadPtr) % m_MaxRecord;
	if ( InSize > errorcode )
	{
		InSize = errorcode;
	}

	copysize = m_MaxRecord - m_HeadPtr;
	if ( copysize >= InSize )
	{
		memcpy(OutBuf,&m_RecordData[m_HeadPtr],InSize);
	}
	else
	{
		memcpy(OutBuf,&m_RecordData[m_HeadPtr],copysize);
		memcpy(OutBuf + copysize,&m_RecordData[0],InSize - copysize);
	}

	m_HeadPtr = (m_HeadPtr + InSize) % m_MaxRecord;

	return(InSize);
}
//#####################################################################################
 template <typename T> bool MCharLoopGroupSt<T>::IsEmpty(void)
{
	if ( m_HeadPtr == m_TailPtr )
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//#####################################################################################
 template <typename T> void MCharLoopGroupSt<T>::Clear(void)
{
	m_TailPtr = m_HeadPtr;
}
//#####################################################################################
//BEGIN_LMYUNIT(MCharLoopGroupMt,MCharLoopGroupSt)

//END_LMYUNITEND_LMYUNIT
//#####################################################################################
 template <typename T> MCharLoopGroupMt<T>::MCharLoopGroupMt(void)
{

}
//#####################################################################################
 template <typename T> MCharLoopGroupMt<T>::~MCharLoopGroupMt()
{
	Release();
}
//#####################################################################################
 template <typename T> int  MCharLoopGroupMt<T>::Instance(unsigned short MaxCount)
{
	register int					errorcode;

	m_Section.Lock();

	errorcode = MCharLoopGroupSt<T>::Instance(MaxCount);

	m_Section.UnLock();

	return(errorcode);
}
//#####################################################################################
 template <typename T> void MCharLoopGroupMt<T>::Release(void)
{
	m_Section.Lock();

	MCharLoopGroupSt<T>::Release();

	m_Section.UnLock();
}
//#####################################################################################
 template <typename T> int  MCharLoopGroupMt<T>::PutData(char * InBuf,unsigned short InSize)
{
	register int					errorcode;

	m_Section.Lock();

	errorcode = MCharLoopGroupSt<T>::PutData(InBuf,InSize);

	m_Section.UnLock();

	return(errorcode);
}
//#####################################################################################
 template <typename T> int  MCharLoopGroupMt<T>::GetData(char * OutBuf,unsigned short InSize)
{
	register int					errorcode;

	m_Section.Lock();

	errorcode = MCharLoopGroupSt<T>::GetData(OutBuf,InSize);

	m_Section.UnLock();

	return(errorcode);
}
//#####################################################################################
 template <typename T>void MCharLoopGroupMt<T>::Clear(void)
{
	m_Section.Lock();

	MCharLoopGroupSt<T>::Clear();

	m_Section.UnLock();
}

#endif
//#####################################################################################
//#####################################################################################
//#####################################################################################
//#####################################################################################
