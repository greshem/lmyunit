#ifndef __HEADER__BUFFER_MANGERF_HEADER
#define __HEADER__BUFFER_MANGERF_HEADER

#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <memory.h>
#define	MAX_STEP		81920
/////////////////////////////////////////////////////////////////////

//本类没有任何加锁的控制，左右的控制有上层应用自行控制
class CBufManage  
{
public:
	CBufManage();
	CBufManage(int type);
	virtual ~CBufManage();
public:
	long	DelData(long del_len,long start=0);		//删除数据
	long	AddData(char * buf,long len);			//添加数据到末尾
	char *	GetBufPtr();							//获取数据指针
	char *	GetBufPtr(long &len);
	long	GetDataLen(); 							//返回当前数据有多大
	int		SetType(int);
private:
	char			*m_Buf;			//缓冲
	long			m_Len;			//缓冲大小
	long			m_MaxLen;		//当前缓冲分配的最大大小
	long			m_Step;			//每次分配的缓冲大小
};




#endif
