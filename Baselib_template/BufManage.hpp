#ifndef __HEADER__BUFFER_MANGERF_HEADER
#define __HEADER__BUFFER_MANGERF_HEADER

#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <memory.h>
#define	MAX_STEP		81920
/////////////////////////////////////////////////////////////////////

//����û���κμ����Ŀ��ƣ����ҵĿ������ϲ�Ӧ�����п���
template< typename T> class CBufManage  
{
public:
	CBufManage();
	CBufManage(int type);
	virtual ~CBufManage();
public:
	long	DelData(long del_len,long start=0);		//ɾ������
	long	AddData(char * buf,long len);			//������ݵ�ĩβ
	char *	GetBufPtr();							//��ȡ����ָ��
	char *	GetBufPtr(long &len);
	long	GetDataLen(); 							//���ص�ǰ�����ж��
	int		SetType(int);
private:
	char			*m_Buf;			//����
	long			m_Len;			//�����С
	long			m_MaxLen;		//��ǰ������������С
	long			m_Step;			//ÿ�η���Ļ����С
};




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//#define NULL '\0'
template < typename T> CBufManage<T>::CBufManage()
{
	m_Buf = NULL;
	m_Len = 0;
	m_MaxLen = 0;
	m_Step = MAX_STEP;
}
 template < typename T> CBufManage<T>::CBufManage(int type)
{
	m_Buf = NULL;
	m_Len = 0;
	m_MaxLen = 0;
	m_Step = MAX_STEP;
}

 template < typename T> CBufManage<T>::~CBufManage()
{
	if(m_Buf!=NULL)
		free(m_Buf);
	m_Buf = NULL;
	m_Len = 0;
	m_MaxLen = 0;
}

 template < typename T> long CBufManage<T>::AddData(char *buf, long len)
{
	long	NeedLen = len + m_Len;
	if(NeedLen >= m_MaxLen)	// ���·����ڴ�
	{
		NeedLen = m_MaxLen + m_Step* (1+(len + m_Step - 1) / m_Step);	//���������С���ڴ�ռ�
		char* newbuffer = (char*)realloc(m_Buf, NeedLen);
		if(newbuffer == NULL)
		{
			//global_Log.WriteError("bufMange", "realloc  ����ʧ��");
			cout<< "realloc  ����ʧ��"<<endl;
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

template < typename T> char * CBufManage<T>::GetBufPtr(long &len)
{
	return m_Buf+len;
}
 template < typename T>int CBufManage<T>::SetType(int type)
{
	return 1;
}

 template < typename T> char * CBufManage<T>::GetBufPtr()
{
	return m_Buf;
}
 template < typename T> long CBufManage<T>::DelData(long del_len, long start)
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

 template < typename T> long CBufManage<T>::GetDataLen()
{
	return m_Len;
}
#endif
