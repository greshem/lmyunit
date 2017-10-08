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
//获取该类的类名称
const char * MRuntimeClass::GetClassName(void)
{
	return(m_ClassName);
}
//.................................................................................................................................
//获取基类运行类信息指针
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
//根据错误代码获取错误信息
MString MErrorCode::GetErrorString(unsigned long ErrorCode)
{
	register MErrorCode				*	tempptr;
	register tagErrorCodeInfo		*	errorcode;
	MString								tempstring;

	if ( (ErrorCode & 0x20000000) == 0 )
	{
		//操作系统错误
		#ifdef WINDOWSCODE
		
		LPVOID							lpmsgabuf;
		
		ErrorCode = ErrorCode & 0x7FFFFFFF;
		//操作系统错误
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
			tempstring = "[MErrorCode]无法获取Windows错误代码的描述信息，ERR：" + MString(ErrorCode);
		}

		return(tempstring);
		
		#else
			
		ErrorCode = ErrorCode & 0x7FFFFFFF;
		tempstring = MString(ErrorCode) + "：";
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

		return("[MErrorCode]无法获取自定义错误代码的描述信息，ERR：" + MString(ErrorCode - ERROR_USER_BASECODE));
	}
}
//---------------------------------------------------------------------------------------------------------------------------------
MRuntimeClass				MObject::static_RuntimeClass("MObject",sizeof(MObject),MObject::CreateObject,NULL);
//.................................................................................................................................
//创建该类对象的函数
MObject * MObject::CreateObject(void)
{
	return(new MObject);
}
//.................................................................................................................................
tagErrorCodeInfo			MObject::static_ErrorTable[] = 
{
	{ERROR_MHASHTABLEST_NODATA,"MHashTableSt","队列中没有发现匹配的数据"},
	{ERROR_MHASHTABLEST_EMPTY,"MHashTableSt","队列为空，不能进行查询操作"},
	{ERROR_MHASHTABLEST_FULL,"MHashTableSt","队列已满，不能加入任何数据"},
	{ERROR_MHASHTABLEST_NOMEMORY,"MHashTableSt","没有足够的空间可以分配"},
	{ERROR_MLOOPGROUPST_FULL,"MLoopGroupSt","队列已满，不能加入任何数据"},
	{ERROR_MLOOPGROUPST_EMPTY,"MLoopGroupSt","队列已空，不能获取任何数据"},
	{ERROR_MLOOPGROUPST_NOMEMORY,"MLoopGroupSt","没有足够的空间可以分配"},
	{ERROR_MSTRING_NOSUBSTRING,"MString","没有匹配的子串"},
	{ERROR_MSTRING_INVALIDOFFSET,"MString","无效的字符偏移量"},
	{0,"MObject","错误代码定义表结束标志"}
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
//获取运行时刻类信息对象
MRuntimeClass * MObject::GetRuntimeClass(void)
{
	return(&MObject::static_RuntimeClass);
}
//---------------------------------------------------------------------------------------------------------------------------------
