//---------------------------------------------------------------------------------------------------------------------------------
#include "mobject.h"
//---------------------------------------------------------------------------------------------------------------------------------
MRuntimeClass			*	MRuntimeClass::static_FirstRuntimeClassPtr = NULL;
//.................................................................................................................................
MRuntimeClass::MRuntimeClass(const char * ClassName,int ClassSize,tagFunInterface_CreateObject * CreateObject,MRuntimeClass * BaseClass)
{
	m_ClassName = ClassName;
	m_ClassSize = ClassSize;
	m_CreateObject = CreateObject;
	m_BaseClass = BaseClass;

	m_NextClass = static_FirstRuntimeClassPtr;
	static_FirstRuntimeClassPtr = this;
}
//.................................................................................................................................
MRuntimeClass::~MRuntimeClass()
{

}
//.................................................................................................................................
//��ȡ�����������
const char * MRuntimeClass::GetClassName(void)
{
	return(m_ClassName);
}
//.................................................................................................................................
//��ȡ������������Ϣָ��
MRuntimeClass * MRuntimeClass::GetBaseClass(void)
{
	return(m_BaseClass);
}
//---------------------------------------------------------------------------------------------------------------------------------
MErrorCode				*	MErrorCode::static_FirstErrorCodePtr = NULL;
//.................................................................................................................................
MErrorCode::MErrorCode(tagErrorCodeInfo * ErrorTable)
{
	m_ErrorTable = ErrorTable;

	m_NextClass = static_FirstErrorCodePtr;
	static_FirstErrorCodePtr = this;
}
//.................................................................................................................................
MErrorCode::~MErrorCode()
{

}
//.................................................................................................................................
//���ݴ�������ȡ������Ϣ
MString MErrorCode::GetErrorString(unsigned long ErrorCode)
{
	register MErrorCode				*	tempptr;
	register tagErrorCodeInfo		*	errorcode;
	MString								tempstring;

	if ( (ErrorCode & 0x20000000) == 0 )
	{
		//����ϵͳ����
		#ifdef WINDOWSCODE
		
		LPVOID							lpmsgabuf;
		
		ErrorCode = ErrorCode & 0x7FFFFFFF;
		//����ϵͳ����
		if ( ::FormatMessage(	FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
								NULL,
								ErrorCode,
								0,
								(LPTSTR) &lpmsgabuf,
								0,
								NULL    ) != 0 && lpmsgabuf != NULL )
		{
			tempstring = (char *)lpmsgabuf;
			::LocalFree(lpmsgabuf);
		}
		else
		{
			tempstring = "[MErrorCode]�޷���ȡWindows��������������Ϣ��ERR��" + MString(ErrorCode);
		}

		return(tempstring);
		
		#else
			
		ErrorCode = ErrorCode & 0x7FFFFFFF;
		tempstring = MString(ErrorCode) + "��";
		tempstring += strerror(ErrorCode);
			
		return(tempstring);
		
		#endif
	}
	else
	{
		tempptr = static_FirstErrorCodePtr;
		while ( tempptr != NULL )
		{
			errorcode = tempptr->m_ErrorTable;
			while ( errorcode != NULL && errorcode->ErrorCode != 0 )
			{
				if ( ErrorCode == errorcode->ErrorCode )
				{
					tempstring = MString("[") + errorcode->ClassName + "]" + errorcode->Content;
					return(tempstring);
				}

				errorcode ++;
			}

			tempptr = tempptr->m_NextClass;
		}

		return("[MErrorCode]�޷���ȡ�Զ����������������Ϣ��ERR��" + MString(ErrorCode - ERROR_USER_BASECODE));
	}
}
//---------------------------------------------------------------------------------------------------------------------------------
MRuntimeClass				MObject::static_RuntimeClass("MObject",sizeof(MObject),MObject::CreateObject,NULL);
//.................................................................................................................................
//�����������ĺ���
MObject * MObject::CreateObject(void)
{
	return(new MObject);
}
//.................................................................................................................................
tagErrorCodeInfo			MObject::static_ErrorTable[] = 
{
	{ERROR_MHASHTABLEST_NODATA,"MHashTableSt","������û�з���ƥ�������"},
	{ERROR_MHASHTABLEST_EMPTY,"MHashTableSt","����Ϊ�գ����ܽ��в�ѯ����"},
	{ERROR_MHASHTABLEST_FULL,"MHashTableSt","�������������ܼ����κ�����"},
	{ERROR_MHASHTABLEST_NOMEMORY,"MHashTableSt","û���㹻�Ŀռ���Է���"},
	{ERROR_MLOOPGROUPST_FULL,"MLoopGroupSt","�������������ܼ����κ�����"},
	{ERROR_MLOOPGROUPST_EMPTY,"MLoopGroupSt","�����ѿգ����ܻ�ȡ�κ�����"},
	{ERROR_MLOOPGROUPST_NOMEMORY,"MLoopGroupSt","û���㹻�Ŀռ���Է���"},
	{ERROR_MSTRING_NOSUBSTRING,"MString","û��ƥ����Ӵ�"},
	{ERROR_MSTRING_INVALIDOFFSET,"MString","��Ч���ַ�ƫ����"},
	{0,"MObject","������붨��������־"}
};
//.................................................................................................................................
MErrorCode					MObject::static_ErrorCode(MObject::static_ErrorTable);
//.................................................................................................................................
MObject::MObject(void)
{

}
//.................................................................................................................................
MObject::~MObject()
{

}
//.................................................................................................................................
//��ȡ����ʱ������Ϣ����
MRuntimeClass * MObject::GetRuntimeClass(void)
{
	return(&MObject::static_RuntimeClass);
}
//---------------------------------------------------------------------------------------------------------------------------------
