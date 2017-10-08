//---------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMObjectH__
#define __LmyUnitMObjectH__
//---------------------------------------------------------------------------------------------------------------------------------
//公共头文件
#include "mstring.h"
//.................................................................................................................................
#ifdef WINDOWSCODE
//.................................................................................................................................
//Windows操作系统
//.................................................................................................................................
#else
//.................................................................................................................................
//Linux操作系统
//.................................................................................................................................
#endif
//---------------------------------------------------------------------------------------------------------------------------------
class MObject;
class MString;
//---------------------------------------------------------------------------------------------------------------------------------
#pragma pack(1)
//---------------------------------------------------------------------------------------------------------------------------------
typedef MObject * tagFunInterface_CreateObject(void);
//.................................................................................................................................
class MRuntimeClass
{
protected:
	static MRuntimeClass			*	static_FirstRuntimeClassPtr;		//所有运行类信息的起始指针
public:
	const char						*	m_ClassName;						//类名称
	int									m_ClassSize;						//类尺寸
	tagFunInterface_CreateObject	*	m_CreateObject;						//类的创建对象函数指针
	MRuntimeClass					*	m_NextClass;						//下一个运行类信息指针
	MRuntimeClass					*	m_BaseClass;						//基类的运行类信息指针
public:
	MRuntimeClass(const char * ClassName,int ClassSize,tagFunInterface_CreateObject * CreateObject,MRuntimeClass * BaseClass);
	virtual ~MRuntimeClass();
public:
	//获取该类的类名称
	const char * GetClassName(void);
	//获取基类运行类信息指针
	MRuntimeClass * GetBaseClass(void);
};
//---------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
	unsigned long						ErrorCode;							//错误编号
	const char						*	ClassName;							//出错类名
	const char						*	Content;							//错误内容
} tagErrorCodeInfo;
//.................................................................................................................................
#ifdef WINDOWSCODE

#define		ERROR_SYSTEM_BASECODE		0x80000000							//系统错误(0x80000000 -- 0x8FFFFFFF)
#define		ERROR_SYSTEM(errorcode)		(ERROR_SYSTEM_BASECODE + errorcode)	//系统错误正规化
#define		ERROR_USER_BASECODE			0xA0000000							//用户错误(0xA0000000 -- 0xAFFFFFFF)
#define		ERROR_USER(errorcode)		(ERROR_USER_BASECODE + errorcode)	//用户错误正规化

#else

#define		ERROR_SYSTEM_BASECODE		0x80000000							//系统错误(0x80000000 -- 0x8FFFFFFF)
#define		ERROR_SYSTEM(errorcode)		(ERROR_SYSTEM_BASECODE + errno)		//系统错误正规化
#define		ERROR_USER_BASECODE			0xA0000000							//用户错误(0xA0000000 -- 0xAFFFFFFF)
#define		ERROR_USER(errorcode)		(ERROR_USER_BASECODE + errorcode)	//用户错误正规化

#endif
//.................................................................................................................................
//模版类特定错误
#define		ERROR_MLOOPGROUPST_NOMEMORY	ERROR_USER(30)						//没有足够的空间可以分配
#define		ERROR_MLOOPGROUPST_FULL		ERROR_USER(31)						//队列已满，不能加入任何数据
#define		ERROR_MLOOPGROUPST_EMPTY	ERROR_USER(32)						//队列已空，不能获取任何数据

#define		ERROR_MHASHTABLEST_NOMEMORY	ERROR_USER(33)						//没有足够的空间可以分配
#define		ERROR_MHASHTABLEST_FULL		ERROR_USER(34)						//队列已满，不能加入任何数据
#define		ERROR_MHASHTABLEST_EMPTY	ERROR_USER(35)						//队列为空，不能进行查询操作
#define		ERROR_MHASHTABLEST_NODATA	ERROR_USER(36)						//队列中没有发现匹配的数据
//.................................................................................................................................
class MErrorCode
{
protected:
	static MErrorCode				*	static_FirstErrorCodePtr;			//所有错误描述类的指针
public:
	MErrorCode						*	m_NextClass;						//下一个错误描述类指针
	tagErrorCodeInfo				*	m_ErrorTable;						//该类所有错误信息的指针
public:
	MErrorCode(tagErrorCodeInfo * ErrorTable);
	virtual ~MErrorCode();
public:
	//根据错误代码获取错误信息
	static MString GetErrorString(unsigned long ErrorCode);
};
//---------------------------------------------------------------------------------------------------------------------------------
class MObject
{
protected:
	static MRuntimeClass				static_RuntimeClass;				//该类的运行时刻类信息对象
	static tagErrorCodeInfo				static_ErrorTable[];				//该类的错误描述表
	static MErrorCode					static_ErrorCode;					//该类的错误描述类
public:
	MObject(void);
	virtual ~MObject();
public:
	//创建该类对象的函数
	static MObject * CreateObject(void);
	//获取运行时刻类信息对象
	virtual MRuntimeClass * GetRuntimeClass(void);
};
//---------------------------------------------------------------------------------------------------------------------------------
#define	DECLARE_LMYUNIT(classname)																\
public:																							\
	static MRuntimeClass				static_RuntimeClass;									\
	static tagErrorCodeInfo				static_ErrorTable[];									\
	static MErrorCode					static_ErrorCode;										\
public:																							\
	virtual MRuntimeClass * GetRuntimeClass(void);												\
	static MObject * CreateObject(void);
//.................................................................................................................................
#define BEGIN_LMYUNIT(classname,baseclass)														\
MRuntimeClass	classname::static_RuntimeClass(#classname,sizeof(classname),classname::CreateObject,&baseclass::static_RuntimeClass);	\
MObject * classname::CreateObject(void)															\
{																								\
	return(new classname);																		\
}																								\
MRuntimeClass * classname::GetRuntimeClass(void)												\
{																								\
	return(&classname::static_RuntimeClass);													\
}																								\
MErrorCode		classname::static_ErrorCode(classname::static_ErrorTable);						\
tagErrorCodeInfo classname::static_ErrorTable[] =												\
{																								\
//.................................................................................................................................
#define END_LMYUNIT																				\
	{0,"MObject","错误代码定义表结束标志"}														\
};
//.................................................................................................................................
#define ERROR_DEFINE(errorcode,classname,errorinfo)												\
	{errorcode,classname,errorinfo},
//---------------------------------------------------------------------------------------------------------------------------------
#pragma pack()
//---------------------------------------------------------------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------------------------------------------------------------
