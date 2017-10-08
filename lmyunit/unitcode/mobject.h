//---------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMObjectH__
#define __LmyUnitMObjectH__
//---------------------------------------------------------------------------------------------------------------------------------
//����ͷ�ļ�
#include "mstring.h"
//.................................................................................................................................
#ifdef WINDOWSCODE
//.................................................................................................................................
//Windows����ϵͳ
//.................................................................................................................................
#else
//.................................................................................................................................
//Linux����ϵͳ
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
	static MRuntimeClass			*	static_FirstRuntimeClassPtr;		//������������Ϣ����ʼָ��
public:
	const char						*	m_ClassName;						//������
	int									m_ClassSize;						//��ߴ�
	tagFunInterface_CreateObject	*	m_CreateObject;						//��Ĵ���������ָ��
	MRuntimeClass					*	m_NextClass;						//��һ����������Ϣָ��
	MRuntimeClass					*	m_BaseClass;						//�������������Ϣָ��
public:
	MRuntimeClass(const char * ClassName,int ClassSize,tagFunInterface_CreateObject * CreateObject,MRuntimeClass * BaseClass);
	virtual ~MRuntimeClass();
public:
	//��ȡ�����������
	const char * GetClassName(void);
	//��ȡ������������Ϣָ��
	MRuntimeClass * GetBaseClass(void);
};
//---------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
	unsigned long						ErrorCode;							//������
	const char						*	ClassName;							//��������
	const char						*	Content;							//��������
} tagErrorCodeInfo;
//.................................................................................................................................
#ifdef WINDOWSCODE

#define		ERROR_SYSTEM_BASECODE		0x80000000							//ϵͳ����(0x80000000 -- 0x8FFFFFFF)
#define		ERROR_SYSTEM(errorcode)		(ERROR_SYSTEM_BASECODE + errorcode)	//ϵͳ�������滯
#define		ERROR_USER_BASECODE			0xA0000000							//�û�����(0xA0000000 -- 0xAFFFFFFF)
#define		ERROR_USER(errorcode)		(ERROR_USER_BASECODE + errorcode)	//�û��������滯

#else

#define		ERROR_SYSTEM_BASECODE		0x80000000							//ϵͳ����(0x80000000 -- 0x8FFFFFFF)
#define		ERROR_SYSTEM(errorcode)		(ERROR_SYSTEM_BASECODE + errno)		//ϵͳ�������滯
#define		ERROR_USER_BASECODE			0xA0000000							//�û�����(0xA0000000 -- 0xAFFFFFFF)
#define		ERROR_USER(errorcode)		(ERROR_USER_BASECODE + errorcode)	//�û��������滯

#endif
//.................................................................................................................................
//ģ�����ض�����
#define		ERROR_MLOOPGROUPST_NOMEMORY	ERROR_USER(30)						//û���㹻�Ŀռ���Է���
#define		ERROR_MLOOPGROUPST_FULL		ERROR_USER(31)						//�������������ܼ����κ�����
#define		ERROR_MLOOPGROUPST_EMPTY	ERROR_USER(32)						//�����ѿգ����ܻ�ȡ�κ�����

#define		ERROR_MHASHTABLEST_NOMEMORY	ERROR_USER(33)						//û���㹻�Ŀռ���Է���
#define		ERROR_MHASHTABLEST_FULL		ERROR_USER(34)						//�������������ܼ����κ�����
#define		ERROR_MHASHTABLEST_EMPTY	ERROR_USER(35)						//����Ϊ�գ����ܽ��в�ѯ����
#define		ERROR_MHASHTABLEST_NODATA	ERROR_USER(36)						//������û�з���ƥ�������
//.................................................................................................................................
class MErrorCode
{
protected:
	static MErrorCode				*	static_FirstErrorCodePtr;			//���д����������ָ��
public:
	MErrorCode						*	m_NextClass;						//��һ������������ָ��
	tagErrorCodeInfo				*	m_ErrorTable;						//�������д�����Ϣ��ָ��
public:
	MErrorCode(tagErrorCodeInfo * ErrorTable);
	virtual ~MErrorCode();
public:
	//���ݴ�������ȡ������Ϣ
	static MString GetErrorString(unsigned long ErrorCode);
};
//---------------------------------------------------------------------------------------------------------------------------------
class MObject
{
protected:
	static MRuntimeClass				static_RuntimeClass;				//���������ʱ������Ϣ����
	static tagErrorCodeInfo				static_ErrorTable[];				//����Ĵ���������
	static MErrorCode					static_ErrorCode;					//����Ĵ���������
public:
	MObject(void);
	virtual ~MObject();
public:
	//�����������ĺ���
	static MObject * CreateObject(void);
	//��ȡ����ʱ������Ϣ����
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
	{0,"MObject","������붨��������־"}														\
};
//.................................................................................................................................
#define ERROR_DEFINE(errorcode,classname,errorinfo)												\
	{errorcode,classname,errorinfo},
//---------------------------------------------------------------------------------------------------------------------------------
#pragma pack()
//---------------------------------------------------------------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------------------------------------------------------------
