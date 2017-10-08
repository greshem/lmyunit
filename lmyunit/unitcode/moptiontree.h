//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMOptionTreeH__
#define __LmyUnitMOptionTreeH__
//--------------------------------------------------------------------------------------------------------------------------------
//����ͷ�ļ�
#include "mobject.h"
//................................................................................................................................
#ifdef WINDOWSCODE
//................................................................................................................................
//Windows����ϵͳ
//................................................................................................................................
#else
//................................................................................................................................
//Linux����ϵͳ
//................................................................................................................................
#endif
//--------------------------------------------------------------------------------------------------------------------------------
#pragma pack(1)
//................................................................................................................................
#define OPTION_ATTR_READABLE	0x01		//�ɶ�
#define OPTION_ATTR_WRITEABLE	0x02		//��д
#define OPTION_ATTR_STATIC		0x04		//��̬����[������Ч]
#define OPTION_ATTR_DYNAMIC		0x08		//��̬����[������Ч]
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
	OPTION_TYPE_STRING,					//�� '\0' ��β���ַ���
	OPTION_TYPE_STRUCT,					//�û��Լ����������	
};
//................................................................................................................................
typedef struct
{
	unsigned long			ChildCount;		//�ýڵ���ֽӵ�����
	char 					Name[32];		//��Ա����
	unsigned char			Type;			//��Ա����
	unsigned short 			Size;			//��Ա��Сsize
	unsigned short			Count;			//��Ա�����count��Ҳ��������Ĵ�С��������������Ϊ1
	char					SizeOfName[32];	//��������ʵ�ʴ�С�����ݳ�Ա�����֡�
	int 					Attr;			//����
	char					Descrip[128];	//��������	
} tagOptionTreeNode;
//................................................................................................................................
#pragma pack()
//--------------------------------------------------------------------------------------------------------------------------------
#define		ERROR_MOPTIONTREE_NOMEMORY		(ERROR_USER(60))				//MOptionTree��ʼ��ʧ��[û���㹻���ڴ���Է���]
#define		ERROR_MOPTIONTREE_OUTBUFSIZE	(ERROR_USER(61))				//MOptionTree����ʧ��[���������̫С������������������]
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
