#include "BufManage.hpp"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//#define NULL '\0'
 CBufManage::CBufManage()
{
	m_Buf = NULL;
	m_Len = 0;
	m_MaxLen = 0;
	m_Step = MAX_STEP;
}
  CBufManage::CBufManage(int type)
{
	m_Buf = NULL;
	m_Len = 0;
	m_MaxLen = 0;
	m_Step = MAX_STEP;
}

  CBufManage::~CBufManage()
{
	if(m_Buf!=NULL)
		free(m_Buf);
	m_Buf = NULL;
	m_Len = 0;
	m_MaxLen = 0;
}

  long CBufManage::AddData(char *buf, long len)
{
	long	NeedLen = len + m_Len;
	if(NeedLen >= m_MaxLen)	// 重新分配内存
	{
		NeedLen = m_MaxLen + m_Step* (1+(len + m_Step - 1) / m_Step);	//获得整数大小的内存空间
		char* newbuffer = (char*)realloc(m_Buf, NeedLen);
		if(newbuffer == NULL)
		{
			//global_Log.WriteError("bufMange", "realloc  分配失败");
			printf("realloc  分配失败\n");
			return -1;
		}	
		m_Buf = newbuffer;
		memset(m_Buf + m_Len, 0 ,NeedLen - m_MaxLen);
		m_MaxLen = NeedLen;
	}
	memcpy(m_Buf + m_Len, buf,len);
	m_Len = m_Len + len;
	return m_Len;
}

 char * CBufManage::GetBufPtr(long &len)
{
	return m_Buf+len;
}
 int CBufManage::SetType(int type)
{
	return 1;
}

  char * CBufManage::GetBufPtr()
{
	return m_Buf;
}
  long CBufManage::DelData(long del_len, long start)
{
	if(start<0 || start >= m_Len)
		return -1;
	long left = m_Len - del_len;
	if(left<=0)
	{
		m_Len = 0;
		return 0;
	}
	memmove(m_Buf + start,m_Buf + start + del_len, left);
	

	m_Len=left;

return left;
}

  long CBufManage::GetDataLen()
{
	return m_Len;
}

