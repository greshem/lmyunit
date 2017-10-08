//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMOptionTreeH__
#define __LmyUnitMOptionTreeH__
//--------------------------------------------------------------------------------------------------------------------------------
//公共头文件
#include "mobject.h"
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
#pragma pack(1)
//................................................................................................................................
#define OPTION_ATTR_READABLE	0x01		//可读
#define OPTION_ATTR_WRITEABLE	0x02		//可写
#define OPTION_ATTR_STATIC		0x04		//静态配置[重启有效]
#define OPTION_ATTR_DYNAMIC		0x08		//动态配置[立即有效]
//................................................................................................................................
enum
{
	OPTION_TYPE_UCHAR = 0,				//unsigned char
	OPTION_TYPE_CHAR,					//char
	OPTION_TYPE_BOOL,					//bool(true,false)
	OPTION_TYPE_USHORT,					//unsigned short
	OPTION_TYPE_SHORT,					//short
	OPTION_TYPE_UINT,					//unsigned int
	OPTION_TYPE_INT,					//int
	OPTION_TYPE_ULONG,					//unsigned long
	OPTION_TYPE_LONG,					//long
	OPTION_TYPE_FLOAT,					//float
	OPTION_TYPE_DOUBLE,					//double
	OPTION_TYPE_STRING,					//以 '\0' 结尾的字符串
	OPTION_TYPE_STRUCT,					//用户自己定义的类型	
};
//................................................................................................................................
typedef struct
{
	unsigned long			ChildCount;		//该节点的字接点数量
	char 					Name[32];		//成员名字
	unsigned char			Type;			//成员类型
	unsigned short 			Size;			//成员大小size
	unsigned short			Count;			//成员数组的count（也就是数组的大小），不是树组则为1
	char					SizeOfName[32];	//描述数组实际大小的数据成员的名字。
	int 					Attr;			//属性
	char					Descrip[128];	//文字描述	
} tagOptionTreeNode;
//................................................................................................................................
#pragma pack()
//--------------------------------------------------------------------------------------------------------------------------------
#define		ERROR_MOPTIONTREE_NOMEMORY		(ERROR_USER(60))				//MOptionTree初始化失败[没有足够的内存可以分配]
#define		ERROR_MOPTIONTREE_OUTBUFSIZE	(ERROR_USER(61))				//MOptionTree操作失败[如果缓冲区太小，不能填入所有数据]
//................................................................................................................................
class MOptionTree : public MObject
{
protected:
	tagOptionTreeNode	*	m_RecordData;
	unsigned short			m_MaxRecord;
	unsigned short			m_RecordCount;
public:
	MOptionTree(void);
	virtual ~MOptionTree();
public:
	int  Instance(unsigned short MaxRecord);
	void Release(void);
public:
	tagOptionTreeNode * AddNode(tagOptionTreeNode * Parent,char * Name,unsigned char Type,unsigned short Size,unsigned short Count,char * SizeOfName,unsigned char Attr,char * Descript);
public:
	unsigned short GetExportBufSize(void);
	int  GetExportBuf(unsigned short Offset,char * OutBuf,unsigned short InSize);

	DECLARE_LMYUNIT(MOptionTree)
};
//--------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------
