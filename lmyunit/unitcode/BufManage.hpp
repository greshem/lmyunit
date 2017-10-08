#ifndef __HEADER__BUFFER_MANGERF_HEADER
#define __HEADER__BUFFER_MANGERF_HEADER

#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <memory.h>
#define	MAX_STEP		81920
/////////////////////////////////////////////////////////////////////

//����û���κμ����Ŀ��ƣ����ҵĿ������ϲ�Ӧ�����п���
class CBufManage  
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




#endif
