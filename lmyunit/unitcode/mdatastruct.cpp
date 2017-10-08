//--------------------------------------------------------------------------------------------------------------------------------
#include "mdatastruct.h"
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MResourceRecordSt,MObject)

	ERROR_DEFINE(ERROR_MRESOURCERECORDST_NOMEMORY,"MResourceRecordSt","没有足够的内存可以分配")
	ERROR_DEFINE(ERROR_MRESOURCERECORDST_FULL,"MResourceRecordSt","资源队列已满，不能加入其他资源")
	ERROR_DEFINE(ERROR_MRESOURCERECORDST_EMPTY,"MResourceRecordSt","没有任何可用资源可以分配")

END_LMYUNIT
//................................................................................................................................
MResourceRecordSt::MResourceRecordSt(void)
{
	m_RecordData = NULL;
	m_MaxRecord = 0;
	m_TailPtr = 0;
	m_HeadPtr = 0;
}
//................................................................................................................................
MResourceRecordSt::~MResourceRecordSt()
{
	Release();
}
//................................................................................................................................
int  MResourceRecordSt::Instance(unsigned short MaxCount)
{
	register int					i;

	Release();

	m_RecordData = new unsigned short[MaxCount + 1];
	if ( m_RecordData == NULL )
	{
		return(ERROR_MRESOURCERECORDST_NOMEMORY);
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
//................................................................................................................................
void MResourceRecordSt::Release(void)
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
int  MResourceRecordSt::GetResource(void)
{
	register unsigned short			errorcode;

	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);

	if ( m_HeadPtr == m_TailPtr )
	{
		return(ERROR_MRESOURCERECORDST_EMPTY);
	}

	errorcode = m_RecordData[m_HeadPtr];
	m_HeadPtr = (m_HeadPtr + 1) % m_MaxRecord;

	return(errorcode);
}
//................................................................................................................................
int  MResourceRecordSt::PutResource(unsigned short ResourceID)
{
	register unsigned short			errorcode;

	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);

	errorcode = (m_TailPtr + 1) % m_MaxRecord;
	if ( errorcode == m_HeadPtr )
	{
		return(ERROR_MRESOURCERECORDST_FULL);
	}

	m_RecordData[m_TailPtr] = ResourceID;
	m_TailPtr = errorcode;

	return(1);
}
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MResourceRecordMt,MResourceRecordSt)

END_LMYUNIT
//................................................................................................................................
MResourceRecordMt::MResourceRecordMt(void)
{

}
//................................................................................................................................
MResourceRecordMt::~MResourceRecordMt()
{
	Release();
}
//................................................................................................................................
int  MResourceRecordMt::Instance(unsigned short MaxCount)
{
	register int					errorcode;

	m_Section.Lock();

	errorcode = MResourceRecordSt::Instance(MaxCount);

	m_Section.UnLock();

	return(errorcode);
}
//................................................................................................................................
void MResourceRecordMt::Release(void)
{
	m_Section.Lock();

	MResourceRecordSt::Release();

	m_Section.UnLock();
}
//................................................................................................................................
int  MResourceRecordMt::GetResource(void)
{
	register int					errorcode;

	m_Section.Lock();

	errorcode = MResourceRecordSt::GetResource();

	m_Section.UnLock();

	return(errorcode);
}
//................................................................................................................................
int  MResourceRecordMt::PutResource(unsigned short ResourceID)
{
	register int					errorcode;

	m_Section.Lock();

	errorcode = MResourceRecordSt::PutResource(ResourceID);

	m_Section.UnLock();

	return(errorcode);
}
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MCharLoopGroupSt,MObject)

	ERROR_DEFINE(ERROR_MCHARLOOPGROUPST_NOMEMORY,"MCharLoopGroupSt","没有足够的内存可以分配")
	ERROR_DEFINE(ERROR_MCHARLOOPGROUPST_FULL,"MCharLoopGroupSt","队列已满，不能加入其他数据")
	ERROR_DEFINE(ERROR_MCHARLOOPGROUPST_EMPTY,"MCharLoopGroupSt","队列为空，不能获取任何数据")

END_LMYUNIT
//................................................................................................................................
MCharLoopGroupSt::MCharLoopGroupSt(void)
{
	m_RecordData = NULL;
	m_MaxRecord = 0;
	m_HeadPtr = 0;
	m_TailPtr = 0;
}
//................................................................................................................................
MCharLoopGroupSt::~MCharLoopGroupSt()
{
	Release();
}
//................................................................................................................................
int  MCharLoopGroupSt::Instance(unsigned short MaxCount)
{
	Release();

	m_RecordData = new char[MaxCount];
	if ( m_RecordData == NULL )
	{
		return(ERROR_MCHARLOOPGROUPST_NOMEMORY);
	}

	m_MaxRecord = MaxCount;
	m_HeadPtr = 0;
	m_TailPtr = 0;

	return(1);
}
//................................................................................................................................
void MCharLoopGroupSt::Release(void)
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
int  MCharLoopGroupSt::PutData(char * InBuf,unsigned short InSize)
{
	register unsigned short				errorcode;
	register unsigned short				copysize;

	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);
	assert(InBuf != NULL);

	errorcode = (m_HeadPtr + m_MaxRecord - m_TailPtr - 1) % m_MaxRecord;
	if ( InSize > errorcode )
	{
		return(ERROR_MCHARLOOPGROUPST_FULL);
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
//................................................................................................................................
int  MCharLoopGroupSt::GetData(char * OutBuf,unsigned short InSize)
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
//................................................................................................................................
bool MCharLoopGroupSt::IsEmpty(void)
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
//................................................................................................................................
void MCharLoopGroupSt::Clear(void)
{
	m_TailPtr = m_HeadPtr;
}
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MCharLoopGroupMt,MCharLoopGroupSt)

END_LMYUNIT
//................................................................................................................................
MCharLoopGroupMt::MCharLoopGroupMt(void)
{

}
//................................................................................................................................
MCharLoopGroupMt::~MCharLoopGroupMt()
{
	Release();
}
//................................................................................................................................
int  MCharLoopGroupMt::Instance(unsigned short MaxCount)
{
	register int					errorcode;

	m_Section.Lock();

	errorcode = MCharLoopGroupSt::Instance(MaxCount);

	m_Section.UnLock();

	return(errorcode);
}
//................................................................................................................................
void MCharLoopGroupMt::Release(void)
{
	m_Section.Lock();

	MCharLoopGroupSt::Release();

	m_Section.UnLock();
}
//................................................................................................................................
int  MCharLoopGroupMt::PutData(char * InBuf,unsigned short InSize)
{
	register int					errorcode;

	m_Section.Lock();

	errorcode = MCharLoopGroupSt::PutData(InBuf,InSize);

	m_Section.UnLock();

	return(errorcode);
}
//................................................................................................................................
int  MCharLoopGroupMt::GetData(char * OutBuf,unsigned short InSize)
{
	register int					errorcode;

	m_Section.Lock();

	errorcode = MCharLoopGroupSt::GetData(OutBuf,InSize);

	m_Section.UnLock();

	return(errorcode);
}
//................................................................................................................................
void MCharLoopGroupMt::Clear(void)
{
	m_Section.Lock();

	MCharLoopGroupSt::Clear();

	m_Section.UnLock();
}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
