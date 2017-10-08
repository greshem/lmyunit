//--------------------------------------------------------------------------------------------------------------------------------
#include "moptiontree.h"
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MOptionTree,MObject)

	ERROR_DEFINE(ERROR_MOPTIONTREE_NOMEMORY,"MOptionTree","初始化失败[没有足够的内存可以分配]")
	ERROR_DEFINE(ERROR_MOPTIONTREE_OUTBUFSIZE,"MOptionTree","操作失败[如果缓冲区太小，不能填入所有数据]")

END_LMYUNIT
//................................................................................................................................
MOptionTree::MOptionTree(void)
{
	m_RecordData = NULL;
	m_MaxRecord = 0;
	m_RecordCount = 0;
}
//................................................................................................................................
MOptionTree::~MOptionTree()
{
	Release();
}
//................................................................................................................................
int  MOptionTree::Instance(unsigned short MaxRecord)
{
	Release();

	m_RecordData = new tagOptionTreeNode[MaxRecord];
	if ( m_RecordData == NULL )
	{
		return(ERROR_MOPTIONTREE_NOMEMORY);
	}

	m_MaxRecord = MaxRecord;
	m_RecordCount = 0;

	return(1);
}
//................................................................................................................................
void MOptionTree::Release(void)
{
	if ( m_RecordData != NULL )
	{
		delete [] m_RecordData;
		m_RecordData = NULL;
	}
	m_MaxRecord = 0;
	m_RecordCount = 0;
}
//................................................................................................................................
tagOptionTreeNode * MOptionTree::AddNode(tagOptionTreeNode * Parent,char * Name,unsigned char Type,unsigned short Size,unsigned short Count,char * SizeOfName,unsigned char Attr,char * Descript)
{
	tagOptionTreeNode			*	tempptr;

	assert(m_RecordCount < m_MaxRecord);
	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);

	m_RecordData[m_RecordCount].ChildCount = 0;				//该节点的字接点数量
	strncpy(m_RecordData[m_RecordCount].Name,Name,32);		//成员名字
	m_RecordData[m_RecordCount].Type = Type;				//成员类型
	m_RecordData[m_RecordCount].Size = Size;				//成员大小size
	m_RecordData[m_RecordCount].Count = Count;				//成员数组的count（也就是数组的大小），不是树组则为0
	strncpy(m_RecordData[m_RecordCount].SizeOfName,SizeOfName,32);//描述数组实际大小的数据成员的名字。
	m_RecordData[m_RecordCount].Attr = Attr;				//属性
	strncpy(m_RecordData[m_RecordCount].Descrip,Descript,128);//文字描述	

	if ( Parent != NULL )
	{
		Parent->ChildCount ++;
	}

	tempptr = &m_RecordData[m_RecordCount];
	m_RecordCount ++;

	return(tempptr);
}
//................................................................................................................................
unsigned short MOptionTree::GetExportBufSize(void)
{
	return(sizeof(tagOptionTreeNode) * m_RecordCount);
}
//................................................................................................................................
int  MOptionTree::GetExportBuf(unsigned short Offset,char * OutBuf,unsigned short InSize)
{
	register short					errorcode;
	char						*	tempptr;

	assert(Offset < sizeof(tagOptionTreeNode) * m_RecordCount);
	if ( Offset > sizeof(tagOptionTreeNode) * m_RecordCount )
	{
		return(ERROR_MOPTIONTREE_OUTBUFSIZE);
	}

	errorcode = min(sizeof(tagOptionTreeNode) * m_RecordCount - Offset,InSize);
	tempptr = (char *)m_RecordData;
	memcpy(OutBuf,tempptr + Offset,errorcode);

	return(errorcode);
}
//--------------------------------------------------------------------------------------------------------------------------------
