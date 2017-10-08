//--------------------------------------------------------------------------------------------------------------------------------
#include "msrvcomm.h"
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MSrvCommLinkQueue,MObject)

	ERROR_DEFINE(ERROR_MSRVCOMMLINKQUEUE_INVALIDLINK,"MSrvComm","执行通讯单元函数错误发生错误[无效的连接号]")
	ERROR_DEFINE(ERROR_MSRVCOMMLINKQUEUE_NODATA,"MSrvComm","执行通讯单元函数错误发生错误[没有匹配的数据]")
	ERROR_DEFINE(ERROR_MSRVCOMMLINKQUEUE_FRAMEHEAD,"MSrvComm","通讯单元接收数据包发生错误[数据包头部错误]")
	ERROR_DEFINE(ERROR_MSRVCOMMLINKQUEUE_SENDFULL,"MSrvComm","通讯单元发送数据包发生错误[缓冲区已满]")
	ERROR_DEFINE(ERROR_MSRVCOMMLINKQUEUE_NOMEMORY,"MSrvComm","通讯单元初始化发生错误[没有足够的内存可以分配]")
	ERROR_DEFINE(ERROR_MSRVCOMMLINKQUEUE_SRVPORT,"MSrvComm","通讯单元创建服务端口发生错误[缓冲区已满]")
	ERROR_DEFINE(ERROR_MSRVCOMMLINKQUEUE_SENDTIMEOUT,"MSrvComm","发送SOCKET数据超时")
	ERROR_DEFINE(ERROR_MSRVCOMMLINKQUEUE_RECVTIMEOUT,"MSrvComm","接收SOCKET数据超时")
	ERROR_DEFINE(ERROR_MSRVCOMMLINKQUEUE_PARAMERROR,"MSrvComm","接收SOCKET数据参数错误")
	ERROR_DEFINE(ERROR_MSRVCOMMLINKQUEUE_CHECKCODE,"MSrvComm","接收SOCKET数据校验错误")
	ERROR_DEFINE(ERROR_MSRVCOMMLINKQUEUE_PARAM,"MSrvComm","发送或接收SOCKET数据参数错误")

END_LMYUNIT
//................................................................................................................................
MSrvCommLinkQueue::MSrvCommLinkQueue(void)
{
	register int					i;

	m_Parent = NULL;
	m_RecordCount = 0;

	for ( i=0;i<=MSRVCOMM_UNIT_LINK_COUNT-1;i++ )
	{
		m_RecordData[i].LinkNo = INVALID_LINK_NO;
		m_RecordData[i].OrderRecord = 0;
	}

	m_LinkTimeOut = 60;
}
//................................................................................................................................
MSrvCommLinkQueue::~MSrvCommLinkQueue()
{
	Release();
}
//................................................................................................................................
int  MSrvCommLinkQueue::Instance(MSrvCommSubUnit * Parent,unsigned long LinkTimeOut)
{
	register int					i;
	register int					errorcode;

	assert(Parent != NULL);

	Release();

	m_Section.Lock();

	if ( (errorcode = m_FreeRecord.Instance(MSRVCOMM_UNIT_LINK_COUNT)) < 0 )
	{
		m_Section.UnLock();
		Release();

		return(errorcode);
	}

	for ( i=0;i<=MSRVCOMM_UNIT_LINK_COUNT-1;i++ )
	{
		m_RecordData[i].LinkNo = INVALID_LINK_NO;
		m_RecordData[i].OrderRecord = 0;
	}

	m_RecordCount = 0;
	m_Parent = Parent;

	m_LinkTimeOut = LinkTimeOut;

	m_Section.UnLock();

	return(1);
}
//................................................................................................................................
void MSrvCommLinkQueue::Release(void)
{
	register int					i;

	m_Section.Lock();

	for ( i=0;i<=MSRVCOMM_UNIT_LINK_COUNT-1;i++ )
	{
		if ( m_RecordData[i].LinkNo != INVALID_LINK_NO )
		{
			closesocket(m_RecordData[i].SocketId);
			m_RecordData[i].LinkNo = INVALID_LINK_NO;
		}
	}

	m_FreeRecord.Release();

	m_RecordCount = 0;

	m_Section.UnLock();
}
//................................................................................................................................
int  MSrvCommLinkQueue::GetSelectSocketInfo(tagSrvCommSelectLinkInfo * Out,unsigned short InSize)
{
	register int					i;
	register int					offset = 0;

	assert(Out != NULL);
	assert(InSize >= MSRVCOMM_UNIT_LINK_COUNT);
	assert(m_Parent != NULL);

	m_Section.Lock();

	for ( i=0;i<=MSRVCOMM_UNIT_LINK_COUNT-1;i++ )
	{
		if ( m_RecordData[i].LinkNo != INVALID_LINK_NO && (m_RecordData[i].LinkType == MSRVCOMM_LINKTYPE_ACCEPT || m_RecordData[i].LinkType == MSRVCOMM_LINKTYPE_LINKSUC) )
		{
			Out[offset].Serial = i;
			Out[offset].LinkNo = m_RecordData[i].LinkNo;
			Out[offset].SocketId = m_RecordData[i].SocketId;

			offset ++;
		}
	}

	m_Section.UnLock();

	return(offset);
}
//................................................................................................................................
int  MSrvCommLinkQueue::GetLinkUnitInfo(tagSrvCommLinkQueue * Out,unsigned short InSize)
{
	assert(Out != NULL);
	assert(InSize >= MSRVCOMM_UNIT_LINK_COUNT);

	m_Section.Lock();

	memcpy((char *)Out,(char *)m_RecordData,sizeof(tagSrvCommLinkQueue) * MSRVCOMM_UNIT_LINK_COUNT);

	m_Section.UnLock();

	return(MSRVCOMM_UNIT_LINK_COUNT);
}
//................................................................................................................................
int  MSrvCommLinkQueue::GetLinkInfo(unsigned short Serial,unsigned long LinkNo,tagSrvCommLinkQueue * Out)
{
	assert(Serial < MSRVCOMM_UNIT_LINK_COUNT);

	m_Section.Lock();

	if ( LinkNo == m_RecordData[Serial].LinkNo )
	{
		memcpy((char *)Out,(char *)&m_RecordData[Serial],sizeof(tagSrvCommLinkQueue));
		m_Section.UnLock();
		return(1);
	}
	else
	{
		m_Section.UnLock();
		return(ERROR_MSRVCOMMLINKQUEUE_INVALIDLINK);
	}
}
//................................................................................................................................
unsigned short MSrvCommLinkQueue::GetLinkCount(void)
{
	register int						errorcode;

	assert(m_Parent != NULL);

	m_Section.Lock();

	errorcode = m_RecordCount;

	m_Section.UnLock();

	return(errorcode);
}
//................................................................................................................................
unsigned long MSrvCommLinkQueue::AddLinkCount(SOCKET SocketId,unsigned long ParentNo,char * IPAddr,unsigned long Port, unsigned short SrvPort, unsigned long LinkType)
{
	register int						serial;
	register unsigned long				linkno;
	tagSrvCommLinkMsg					linkmsg;

	assert(SocketId != INVALID_SOCKET);
	assert(IPAddr != NULL);
	assert(m_Parent != NULL);

	m_Section.Lock();

	if ( (serial = m_FreeRecord.GetResource()) < 0 )
	{
		m_Section.UnLock();

		return(INVALID_LINK_NO);
	}

	linkno = ((unsigned long)m_Parent->m_UnitSerial << 16) | (serial * 1000 + m_RecordData[serial].OrderRecord);
	m_RecordData[serial].OrderRecord = (m_RecordData[serial].OrderRecord + 1) % 1000;

	m_RecordData[serial].LinkNo = linkno;
	m_RecordData[serial].ParentNo = ParentNo;
	m_RecordData[serial].SocketId = SocketId;
	strncpy(m_RecordData[serial].IPAddr,IPAddr,16);
	m_RecordData[serial].SrvPort = SrvPort;
	m_RecordData[serial].Port = Port;
	m_RecordData[serial].LinkType = LinkType;
	m_RecordData[serial].LinkTime.GetCurTickCount();
	m_RecordData[serial].RecvSize = 0;
	m_RecordData[serial].RecvTime.GetCurTickCount();
	m_RecordData[serial].SendSize = 0;
	m_RecordData[serial].SendTime.GetCurTickCount();
	m_RecordData[serial].AddtionData = 0;

	m_RecordCount ++;

	m_Parent->m_RecvWaitEvent.ActiveEvent();
	m_Parent->m_SendWaitEvent.ActiveEvent();

	m_Section.UnLock();

	m_Parent->m_RecvQueue.Resert(serial,linkno);
	m_Parent->m_SendQueue.Resert(serial,linkno,SocketId);
	m_Parent->m_RecvTable.Resert(serial,linkno);

	linkmsg.MsgType = MSRVCOMM_LINKMSG_ADD;
	linkmsg.LinkNo = linkno;
	linkmsg.ParentNo = ParentNo;
	strncpy(linkmsg.IPAddr,IPAddr,16);
	linkmsg.Port = Port;
	linkmsg.LinkType = LinkType;
	linkmsg.AddtionData = 0;
	linkmsg.CloseType = 0;

	m_Parent->m_RecvQueue.AddLinkMsg(&linkmsg);

	return(linkno);
}
//................................................................................................................................
int  MSrvCommLinkQueue::CloseLink(unsigned short Serial,unsigned long LinkNo,unsigned char CloseType)
{
	tagSrvCommLinkMsg					linkmsg;

	assert(Serial < MSRVCOMM_UNIT_LINK_COUNT);
	assert(LinkNo != INVALID_LINK_NO);
	assert(m_Parent != NULL);

	m_Section.Lock();

	if ( m_RecordData[Serial].LinkNo != LinkNo )
	{
		m_Section.UnLock();

		return(ERROR_MSRVCOMMLINKQUEUE_INVALIDLINK);
	}

	linkmsg.MsgType = MSRVCOMM_LINKMSG_CLOSE;
	linkmsg.LinkNo = m_RecordData[Serial].LinkNo;
	linkmsg.ParentNo = m_RecordData[Serial].ParentNo;
	strncpy(linkmsg.IPAddr,m_RecordData[Serial].IPAddr,16);
	linkmsg.Port = m_RecordData[Serial].Port;
	linkmsg.LinkType = m_RecordData[Serial].LinkType;
	linkmsg.AddtionData = m_RecordData[Serial].AddtionData;
	linkmsg.CloseType = CloseType;

	closesocket(m_RecordData[Serial].SocketId);
	m_RecordData[Serial].LinkNo = INVALID_LINK_NO;

	m_RecordCount --;

	m_FreeRecord.PutResource(Serial);

	m_Parent->m_RecvWaitEvent.ActiveEvent();
	m_Parent->m_SendWaitEvent.ActiveEvent();

	m_Section.UnLock();

	m_Parent->m_RecvQueue.Resert(Serial,INVALID_LINK_NO);
	m_Parent->m_SendQueue.Resert(Serial,INVALID_LINK_NO,INVALID_SOCKET);
	m_Parent->m_RecvTable.Resert(Serial,INVALID_LINK_NO);

	m_Parent->m_RecvQueue.AddLinkMsg(&linkmsg);

	return(1);
}
//................................................................................................................................
int   MSrvCommLinkQueue::UpdateRecvInfo(unsigned short Serial,unsigned long LinkNo,unsigned short In)
{
	assert(Serial < MSRVCOMM_UNIT_LINK_COUNT);
	assert(LinkNo != INVALID_LINK_NO);
	assert(In <= MAX_FRAME_SIZE);
	assert(m_Parent != NULL);

	m_Section.Lock();

	if ( m_RecordData[Serial].LinkNo != LinkNo )
	{
		m_Section.UnLock();
		return(ERROR_MSRVCOMMLINKQUEUE_INVALIDLINK);
	}

	m_RecordData[Serial].RecvSize += In;
	m_RecordData[Serial].RecvTime.GetCurTickCount();

	m_Section.UnLock();

	return(1);
}
//................................................................................................................................
int  MSrvCommLinkQueue::UpdateSendInfo(unsigned short Serial,unsigned long LinkNo,unsigned short In)
{
	assert(Serial < MSRVCOMM_UNIT_LINK_COUNT);
	assert(LinkNo != INVALID_LINK_NO);
	assert(m_Parent != NULL);

	m_Section.Lock();

	if ( m_RecordData[Serial].LinkNo != LinkNo )
	{
		m_Section.UnLock();
		return(ERROR_MSRVCOMMLINKQUEUE_INVALIDLINK);
	}

	m_RecordData[Serial].SendSize += In;
	m_RecordData[Serial].SendTime.GetCurTickCount();

	m_Section.UnLock();

	return(1);
}
//................................................................................................................................
void MSrvCommLinkQueue::RefreshTimeOutLink(void)
{
	register int						i;
	tagSrvCommLinkMsg					linkmsg;

	m_Section.Lock();

	for ( i=0;i<=MSRVCOMM_UNIT_LINK_COUNT-1;i++ )
	{
		if ( m_RecordData[i].LinkNo != INVALID_LINK_NO )
		{
			if (	m_RecordData[i].RecvTime.GetDuration() >= ( m_LinkTimeOut * 1000 ) &&
					m_RecordData[i].SendTime.GetDuration() >= ( m_LinkTimeOut * 1000 )	)
			{
				linkmsg.MsgType = MSRVCOMM_LINKMSG_CLOSE;
				linkmsg.LinkNo = m_RecordData[i].LinkNo;
				linkmsg.ParentNo = m_RecordData[i].ParentNo;
				strncpy(linkmsg.IPAddr,m_RecordData[i].IPAddr,16);
				linkmsg.Port = m_RecordData[i].Port;
				linkmsg.LinkType = m_RecordData[i].LinkType;
				linkmsg.AddtionData = m_RecordData[i].AddtionData;
				linkmsg.CloseType = MSRVCOMM_CLOSETYPE_TIMEOUT;

				closesocket(m_RecordData[i].SocketId);
				m_RecordData[i].LinkNo = INVALID_LINK_NO;

				m_RecordCount --;

				m_FreeRecord.PutResource(i);

				m_Parent->m_RecvWaitEvent.ActiveEvent();
				m_Parent->m_SendWaitEvent.ActiveEvent();

				m_Section.UnLock();

				m_Parent->m_RecvQueue.Resert(i,INVALID_LINK_NO);
				m_Parent->m_SendQueue.Resert(i,INVALID_LINK_NO,INVALID_SOCKET);
				m_Parent->m_RecvTable.Resert(i,INVALID_LINK_NO);

				m_Parent->m_RecvQueue.AddLinkMsg(&linkmsg);

				m_Section.Lock();
			}
		}
	}

	m_Section.UnLock();
}
//................................................................................................................................
int   MSrvCommLinkQueue::SetLinkAddtionData(unsigned short Serial,unsigned long LinkNo,unsigned long AddtionData)
{
	assert(Serial < MSRVCOMM_UNIT_LINK_COUNT);
	assert(LinkNo != INVALID_LINK_NO);
	assert(m_Parent != NULL);

	m_Section.Lock();

	if ( m_RecordData[Serial].LinkNo != LinkNo )
	{
		m_Section.UnLock();
		return(ERROR_MSRVCOMMLINKQUEUE_INVALIDLINK);
	}

	m_RecordData[Serial].AddtionData = AddtionData;

	m_Section.UnLock();

	return(1);
}
//................................................................................................................................
int  MSrvCommLinkQueue::GetLinkAddtionData(unsigned short Serial,unsigned long LinkNo,unsigned long * AddtionData)
{
	assert(Serial < MSRVCOMM_UNIT_LINK_COUNT);
	assert(LinkNo != INVALID_LINK_NO);
	assert(m_Parent != NULL);

	m_Section.Lock();

	if ( m_RecordData[Serial].LinkNo != LinkNo && LinkNo != BROADCAST_LINK_NO )
	{
		m_Section.UnLock();
		return(ERROR_MSRVCOMMLINKQUEUE_INVALIDLINK);
	}

	* AddtionData = m_RecordData[Serial].AddtionData;

	m_Section.UnLock();

	return(1);
}
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MSrvCommRecvGroup,MObject)

END_LMYUNIT
//................................................................................................................................
MSrvCommRecvGroup::MSrvCommRecvGroup(void)
{
	m_LinkNo = INVALID_LINK_NO;
	m_WaitRequestCount = 0;
}
//................................................................................................................................
MSrvCommRecvGroup::~MSrvCommRecvGroup()
{
	Release();
}
//................................................................................................................................
int  MSrvCommRecvGroup::Instance(void)
{
	register int					errorcode;

	Release();

	m_Section.Lock();

	if ( (errorcode = m_RecordData.Instance(MSRVCOMM_LINK_RECVSIZE)) < 0 )
	{
		m_Section.UnLock();

		return(errorcode);
	}

	m_LinkNo = INVALID_LINK_NO;
	m_WaitRequestCount = 0;

	m_Section.UnLock();

	return(1);
}
//................................................................................................................................
void MSrvCommRecvGroup::Release(void)
{
	m_Section.Lock();

	m_RecordData.Release();

	m_LinkNo = INVALID_LINK_NO;
	m_WaitRequestCount = 0;

	m_Section.UnLock();
}
//................................................................................................................................
int  MSrvCommRecvGroup::PutData(unsigned long LinkNo,char * InBuf,unsigned short InSize)
{
	register int					errorcode;

	assert(LinkNo != INVALID_LINK_NO);
	assert(InBuf != NULL);
	assert(InSize <= MAX_FRAME_SIZE);

	m_Section.Lock();

	if ( LinkNo != m_LinkNo || m_WaitRequestCount >= MSRVCOMM_LINK_RECVCOUNT )
	{
		m_Section.UnLock();

		MSrvCommUnit::staticLostRequestCount ++;

		return(ERROR_MSRVCOMMLINKQUEUE_INVALIDLINK);
	}

	if ( (errorcode = m_RecordData.PutData(InBuf,InSize)) < 0 )
	{
		m_Section.UnLock();

		MSrvCommUnit::staticLostRequestCount ++;

		return(errorcode);
	}

	m_WaitRequestCount ++;

	m_Section.UnLock();

	return(1);
}
//................................................................................................................................
int  MSrvCommRecvGroup::GetData(unsigned long LinkNo,tagFrameHead * OutHead,char * OutBuf,unsigned short InSize)
{
	register int					errorcode;

	assert(LinkNo != INVALID_LINK_NO);
	assert(OutHead != NULL);
	assert(OutBuf != NULL);
	assert(InSize >= MAX_DATAFRAME_SIZE);

	m_Section.Lock();

	if ( LinkNo != m_LinkNo )
	{
		m_Section.UnLock();
		return(ERROR_MSRVCOMMLINKQUEUE_INVALIDLINK);
	}

	if ( (errorcode = m_RecordData.GetData((char *)OutHead,sizeof(tagFrameHead)) != sizeof(tagFrameHead)) )
	{
		m_Section.UnLock();

		return(errorcode);
	}

	if ( (errorcode = m_RecordData.GetData(OutBuf,OutHead->DataSize)) != OutHead->DataSize )
	{
		m_Section.UnLock();

		return(errorcode);
	}

	m_WaitRequestCount --;

	m_Section.UnLock();

	return(OutHead->DataSize);
}
//................................................................................................................................
void MSrvCommRecvGroup::Resert(unsigned long LinkNo)
{
	m_Section.Lock();

	if ( m_LinkNo != LinkNo )
	{
		m_RecordData.Clear();
		m_LinkNo = LinkNo;

		m_WaitRequestCount = 0;
	}

	m_Section.UnLock();
}
//................................................................................................................................
bool MSrvCommRecvGroup::IsEmpty(unsigned long * LinkNo)
{
	register bool						flag;

	assert(LinkNo != NULL);

	m_Section.Lock();

	flag = m_RecordData.IsEmpty();
	* LinkNo = m_LinkNo;

	m_Section.UnLock();

	return(flag);
}
//................................................................................................................................
unsigned short MSrvCommRecvGroup::GetWaitRequestCount(void)
{
	register unsigned short				errorcode;

	m_Section.Lock();

	errorcode = m_WaitRequestCount;

	m_Section.UnLock();

	return(errorcode);
}
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MSrvCommRecvQueue,MObject)

END_LMYUNIT
//................................................................................................................................
MSrvCommRecvQueue::MSrvCommRecvQueue(void)
{

}
//................................................................................................................................
MSrvCommRecvQueue::~MSrvCommRecvQueue()
{
	Release();
}
//................................................................................................................................
int  MSrvCommRecvQueue::Instance(MSrvCommSubUnit * Parent)
{
	register int					i;
	register int					errorcode;

	assert(Parent != NULL);

	Release();

	if ( (errorcode = m_WaitEvent.Instance()) < 0 )
	{
		Release();
		return(errorcode);
	}

	for ( i=0;i<=MSRVCOMM_UNIT_LINK_COUNT-1;i++ )
	{
		if ( (errorcode = m_RecordData[i].Instance()) < 0 )
		{
			Release();
			return(errorcode);
		}
	}

	if ( (errorcode = m_MsgRecord.Instance(MSRVCOMM_UNIT_LINK_COUNT * 20)) < 0 )
	{
		Release();
		return(errorcode);
	}

	return(1);
}
//................................................................................................................................
void MSrvCommRecvQueue::Release(void)
{
	register int					i;

	m_MsgRecord.Release();

	for ( i=0;i<=MSRVCOMM_UNIT_LINK_COUNT-1;i++ )
	{
		m_RecordData[i].Release();
	}

	m_WaitEvent.Release();
}
//................................................................................................................................
int  MSrvCommRecvQueue::PutData(unsigned short Serial,unsigned long LinkNo,char * InBuf,unsigned short InSize)
{
	assert(Serial < MSRVCOMM_UNIT_LINK_COUNT);

	m_WaitEvent.ActiveEvent();

	return(m_RecordData[Serial].PutData(LinkNo,InBuf,InSize));
}
//................................................................................................................................
int  MSrvCommRecvQueue::RecvFrame(unsigned long LinkNo,tagFrameHead * OutHead,char * OutBuf,unsigned short InSize)
{
	register int						serial;

	serial = MSRVCOMM_LINKORDER(LinkNo);
	assert(serial < MSRVCOMM_UNIT_LINK_COUNT);

	return(m_RecordData[serial].GetData(LinkNo,OutHead,OutBuf,InSize));
}
//................................................................................................................................
int  MSrvCommRecvQueue::AddLinkMsg(tagSrvCommLinkMsg * Msg)
{
	m_WaitEvent.ActiveEvent();

	return(m_MsgRecord.PutData(Msg));
}
//................................................................................................................................
void MSrvCommRecvQueue::Resert(unsigned short Serial,unsigned long LinkNo)
{
	assert(Serial < MSRVCOMM_UNIT_LINK_COUNT);
	m_RecordData[Serial].Resert(LinkNo);
}
//................................................................................................................................
int  MSrvCommRecvQueue::Select(tagSrvCommLinkMsgQueue * LinkMsg,tagSrvCommDataMsgQueue * DataMsg)
{
	register int						i;

	assert(LinkMsg != NULL);
	assert(DataMsg != NULL);

	LinkMsg->LinkCount = 0;
	while ( LinkMsg->LinkCount < MSRVCOMM_UNIT_LINK_COUNT && m_MsgRecord.GetData(&LinkMsg->LinkMsg[LinkMsg->LinkCount]) > 0 )
	{
		LinkMsg->LinkCount ++;
	}

	DataMsg->LinkCount = 0;
	for ( i=0;i<=MSRVCOMM_UNIT_LINK_COUNT-1;i++ )
	{
		if ( m_RecordData[i].IsEmpty(&DataMsg->LinkNo[DataMsg->LinkCount]) == false )
		{
			DataMsg->LinkCount ++;
		}
	}

	if ( LinkMsg->LinkCount == 0 && DataMsg->LinkCount == 0 )
	{
		m_WaitEvent.WaitUntilActive(10);
		return(ERROR_MSRVCOMMLINKQUEUE_NODATA);
	}
	else
	{
		return(1);
	}
}
//................................................................................................................................
unsigned short MSrvCommRecvQueue::GetWaitRequestCount(void)
{
	register int						i;
	register short						errorcode = 0;

	for ( i=0;i<=MSRVCOMM_UNIT_LINK_COUNT-1;i++ )
	{
		errorcode += m_RecordData[i].GetWaitRequestCount();
	}

	return(errorcode);
}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MSrvCommRecvTable,MObject)

END_LMYUNIT
//................................................................................................................................
MSrvCommRecvTable::MSrvCommRecvTable(void)
{
	m_Parent = NULL;
}
//................................................................................................................................
MSrvCommRecvTable::~MSrvCommRecvTable()
{
	Release();
}
//................................................................................................................................
int  MSrvCommRecvTable::Instance(MSrvCommSubUnit * Parent)
{
	register int					i;

	assert(Parent != NULL);

	Release();

	m_Section.Lock();

	for ( i=0;i<=MSRVCOMM_UNIT_LINK_COUNT-1;i++ )
	{
		m_RecordData[i].LinkNo = INVALID_LINK_NO;
		m_RecordData[i].RecvSize = 0;
	}

	m_Parent = Parent;

	m_Section.UnLock();

	return(1);
}
//................................................................................................................................
void MSrvCommRecvTable::Release(void)
{
	register int					i;

	m_Section.Lock();

	for ( i=0;i<=MSRVCOMM_UNIT_LINK_COUNT-1;i++ )
	{
		m_RecordData[i].LinkNo = INVALID_LINK_NO;
		m_RecordData[i].RecvSize = 0;
	}

	m_Parent = NULL;

	m_Section.UnLock();
}
//................................................................................................................................
int  MSrvCommRecvTable::RecvSocketData(unsigned short Serial,unsigned long LinkNo,SOCKET InSocket)
{
	char							tempbuf[MAX_FRAME_SIZE];
	register int					errorcode;
	register int					offset;
	register tagFrameHead		*	mainhead;
	MCRC16							crcclass;
	register int					temperrorcode;

	assert(Serial < MSRVCOMM_UNIT_LINK_COUNT);
	assert(LinkNo != INVALID_LINK_NO);
	assert(InSocket != INVALID_SOCKET);
	assert(m_Parent != NULL);

	
	m_Section.Lock();

	if ( m_RecordData[Serial].LinkNo != LinkNo )
	{
		m_Section.UnLock();
#ifdef WINDOWSCODE
		if ( (errorcode = recv(InSocket,tempbuf,MAX_FRAME_SIZE,0)) <= 0 )
#else
		if ( (errorcode = recv(InSocket,tempbuf,MAX_FRAME_SIZE,MSG_NOSIGNAL)) <= 0 )
#endif
		{
			temperrorcode = ERROR_SYSTEM(WSAGetLastError());
			closesocket(InSocket);
		}

		MSrvCommUnit::UpdateRecvSize(errorcode);

		return(temperrorcode);
	}
#ifdef WINDOWSCODE
	errorcode = recv(InSocket,m_RecordData[Serial].RecvBuf + m_RecordData[Serial].RecvSize,MAX_FRAME_SIZE - m_RecordData[Serial].RecvSize,0);
#else
	errorcode = recv(InSocket,m_RecordData[Serial].RecvBuf + m_RecordData[Serial].RecvSize,MAX_FRAME_SIZE - m_RecordData[Serial].RecvSize,MSG_NOSIGNAL);
#endif
	
	if ( errorcode <= 0 )
	{
		m_Section.UnLock();

		m_Parent->m_LinkQueue.CloseLink(Serial,LinkNo,MSRVCOMM_CLOSETYPE_CLIENT);

		return(0);
	}

	MSrvCommUnit::UpdateRecvSize(errorcode);

	m_RecordData[Serial].RecvSize += errorcode;
	offset = 0;
	
	if ( m_RecordData[Serial].RecvBuf[0] != '$' )
	{
		//对连接的第一个字符不是$的连接进行断开操作，不必等待到一个包头
		m_Section.UnLock();
		
		m_Parent->m_LinkQueue.CloseLink(Serial,LinkNo,MSRVCOMM_CLOSETYPE_RECV);
		
		return(ERROR_MSRVCOMMLINKQUEUE_FRAMEHEAD);
	}

	while ( (m_RecordData[Serial].RecvSize - offset) >= sizeof(tagFrameHead) )
	{
		mainhead = (tagFrameHead *)(m_RecordData[Serial].RecvBuf + offset);
		if ( mainhead->Market != '$' )
		{
			m_Section.UnLock();

			m_Parent->m_LinkQueue.CloseLink(Serial,LinkNo,MSRVCOMM_CLOSETYPE_RECV);

			return(ERROR_MSRVCOMMLINKQUEUE_FRAMEHEAD);
		}

		if ( mainhead->DataSize > MAX_DATAFRAME_SIZE )
		{
			m_Section.UnLock();

			m_Parent->m_LinkQueue.CloseLink(Serial,LinkNo,MSRVCOMM_CLOSETYPE_RECV);

			return(ERROR_MSRVCOMMLINKQUEUE_FRAMEHEAD);
		}

		if ( (offset + sizeof(tagFrameHead) + mainhead->DataSize) > m_RecordData[Serial].RecvSize )
		{
			break;
		}

		if ( (mainhead->DataStatus & 0xC0) != 0 )
		{
			if ( crcclass.CheckCode(m_RecordData[Serial].RecvBuf + offset + sizeof(tagFrameHead),mainhead->DataSize) != mainhead->CheckCode )
			{
				m_Section.UnLock();

				m_Parent->m_LinkQueue.CloseLink(Serial,LinkNo,MSRVCOMM_CLOSETYPE_RECV);

				return(ERROR_MSRVCOMMLINKQUEUE_FRAMEHEAD);
			}
		}

		m_Parent->m_RecvQueue.PutData(Serial,LinkNo,m_RecordData[Serial].RecvBuf + offset,sizeof(tagFrameHead) + mainhead->DataSize);
		offset += sizeof(tagFrameHead) + mainhead->DataSize;
	}

	if ( offset > 0 )
	{
		m_RecordData[Serial].RecvSize -= offset;
		if ( m_RecordData[Serial].RecvSize != 0 )
		{
			memmove(m_RecordData[Serial].RecvBuf,m_RecordData[Serial].RecvBuf + offset,m_RecordData[Serial].RecvSize);
		}

		m_Section.UnLock();

		m_Parent->m_LinkQueue.UpdateRecvInfo(Serial,LinkNo,offset);

		return(1);
	}

	m_Section.UnLock();

	return(1);
}
//................................................................................................................................
void MSrvCommRecvTable::Resert(unsigned short Serial,unsigned long LinkNo)
{
	assert(Serial < MSRVCOMM_UNIT_LINK_COUNT);
	assert(m_Parent != NULL);

	m_Section.Lock();

	if ( m_RecordData[Serial].LinkNo != LinkNo )
	{
		m_RecordData[Serial].RecvSize = 0;
		m_RecordData[Serial].LinkNo = LinkNo;
	}

	m_Section.UnLock();
}
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MSrvCommSendGroup,MObject)

END_LMYUNIT
//................................................................................................................................
MSrvCommSendGroup::MSrvCommSendGroup(void)
{
	m_HeadPtr = 0;
	m_TailPtr = 0;
	m_LinkNo = INVALID_LINK_NO;
	m_SocketId = INVALID_SOCKET;
	m_CloseFlag = false;
	m_Parent = NULL;
}
//................................................................................................................................
MSrvCommSendGroup::~MSrvCommSendGroup()
{
	Release();
}
//................................................................................................................................
int  MSrvCommSendGroup::Instance(MSrvCommSendQueue * Parent)
{
	assert(Parent != NULL);

	Release();

	m_Section.Lock();

	m_HeadPtr = 0;
	m_TailPtr = 0;
	m_LinkNo = INVALID_LINK_NO;
	m_SocketId = INVALID_SOCKET;
	m_CloseFlag = false;
	m_Parent = Parent;

	m_Section.UnLock();

	return(1);
}
//................................................................................................................................
void MSrvCommSendGroup::Release(void)
{
	m_Section.Lock();

	m_HeadPtr = 0;
	m_TailPtr = 0;
	m_LinkNo = INVALID_LINK_NO;
	m_SocketId = INVALID_SOCKET;
	m_CloseFlag = false;
	m_Parent = NULL;

	m_Section.UnLock();
}
//................................................................................................................................
int  MSrvCommSendGroup::SendSocketData(unsigned short Serial,unsigned long LinkNo,SOCKET InSocket)
{
	register int						errorcode;
	register int						sendsize;
	register int						temperrorcode;

	assert(LinkNo != INVALID_LINK_NO);
	assert(InSocket != INVALID_SOCKET);
	assert(m_Parent != NULL);

	m_Section.Lock();

	if ( m_LinkNo == LinkNo && m_SocketId == InSocket && m_HeadPtr == m_TailPtr && m_CloseFlag == true )
	{
		//处理柔和关闭的连接
		m_Section.UnLock();
		m_Parent->m_Parent->m_LinkQueue.CloseLink(Serial,LinkNo,MSRVCOMM_CLOSETYPE_SRV);
		return(1);
	}
	else if ( m_LinkNo != LinkNo || m_SocketId != InSocket || m_HeadPtr == m_TailPtr )
	{
		m_Section.UnLock();
		return(ERROR_MSRVCOMMLINKQUEUE_INVALIDLINK);
	}

	if ( m_TailPtr > m_HeadPtr )
	{
		sendsize = m_TailPtr - m_HeadPtr;
	}
	else
	{
		sendsize = MSRVCOMM_LINK_SENDSIZE - m_HeadPtr;
	}
#ifdef WINDOWSCODE
	errorcode = send(InSocket,m_RecordData + m_HeadPtr,sendsize,0);
#else
	errorcode = send(InSocket,m_RecordData + m_HeadPtr,sendsize,MSG_NOSIGNAL);
#endif
	if ( errorcode < 0 )
	{
		temperrorcode = ERROR_SYSTEM(WSAGetLastError());

		m_Section.UnLock();
		m_Parent->m_Parent->m_LinkQueue.CloseLink(Serial,LinkNo,MSRVCOMM_CLOSETYPE_SEND);
		return(temperrorcode);
	}

	MSrvCommUnit::UpdateSendSize(errorcode);

	m_HeadPtr = (m_HeadPtr + errorcode) % MSRVCOMM_LINK_SENDSIZE;

	m_Section.UnLock();
	m_Parent->m_Parent->m_LinkQueue.UpdateSendInfo(Serial,LinkNo,errorcode);
	return(2);
}
//................................................................................................................................
bool MSrvCommSendGroup::IsEmpty(unsigned long * LinkNo,SOCKET * SocketId)
{
	assert(LinkNo != NULL);
	assert(SocketId != NULL);
	assert(m_Parent != NULL);

	m_Section.Lock();

	if ( m_LinkNo != INVALID_LINK_NO && m_SocketId != INVALID_SOCKET && (m_HeadPtr != m_TailPtr || m_CloseFlag == true) )
	{
		* LinkNo = m_LinkNo;
		* SocketId = m_SocketId;

		m_Section.UnLock();

		return(false);
	}

	m_Section.UnLock();

	return(true);
}
//................................................................................................................................
void MSrvCommSendGroup::Resert(unsigned long LinkNo,SOCKET SocketId)
{
	assert(m_Parent != NULL);

	m_Section.Lock();

	if ( LinkNo != m_LinkNo )
	{
		m_TailPtr = m_HeadPtr;
		m_LinkNo = LinkNo;
		m_SocketId = SocketId;
		m_CloseFlag = false;
	}

	m_Section.UnLock();
}
//................................................................................................................................
int  MSrvCommSendGroup::CloseLink(unsigned long LinkNo)
{
	assert(m_Parent != NULL);

	m_Section.Lock();

	if ( m_LinkNo == LinkNo )
	{
		m_CloseFlag = true;

		m_Section.UnLock();
		return(1);
	}

	m_Section.UnLock();
	return(ERROR_MSRVCOMMLINKQUEUE_INVALIDLINK);
}
//................................................................................................................................
int  MSrvCommSendGroup::SendFrame(unsigned long LinkNo,tagFrameHead * InHead,char * InBuf,unsigned short InSize)
{
	register unsigned long				errorcode;
	register unsigned long				copysize;

	assert(m_Parent != NULL);
	assert(InSize <= MAX_DATAFRAME_SIZE);

	m_Section.Lock();

	if ( LinkNo != BROADCAST_LINK_NO )
	{
		if ( m_LinkNo == INVALID_LINK_NO || m_LinkNo != LinkNo || m_CloseFlag == true )
		{
			m_Section.UnLock();
			return(ERROR_MSRVCOMMLINKQUEUE_INVALIDLINK);
		}
	}
	else
	{
		if ( m_LinkNo == INVALID_LINK_NO || m_CloseFlag == true )
		{
			m_Section.UnLock();
			return(ERROR_MSRVCOMMLINKQUEUE_INVALIDLINK);
		}
	}

	errorcode = (m_HeadPtr + MSRVCOMM_LINK_SENDSIZE - m_TailPtr - 1) % MSRVCOMM_LINK_SENDSIZE;
	if ( (InSize + sizeof(tagFrameHead)) > errorcode )
	{
		m_Section.UnLock();

		MSrvCommUnit::staticLostSendCount ++;

		return(ERROR_MSRVCOMMLINKQUEUE_SENDFULL);
	}

	//拷贝网络消息头部
	copysize = MSRVCOMM_LINK_SENDSIZE - m_TailPtr;
	if ( copysize >= sizeof(tagFrameHead) )
	{
		memcpy(m_RecordData + m_TailPtr,(char *)InHead,sizeof(tagFrameHead));
	}
	else
	{
		memcpy(m_RecordData + m_TailPtr,(char *)InHead,copysize);
		memcpy(m_RecordData,(char *)InHead + copysize,sizeof(tagFrameHead) - copysize);
	}

	m_TailPtr = (m_TailPtr + sizeof(tagFrameHead)) % MSRVCOMM_LINK_SENDSIZE;

	if ( InSize != 0 )
	{
		//拷贝网络消息内容
		copysize = MSRVCOMM_LINK_SENDSIZE - m_TailPtr;
		if ( copysize >= InSize )
		{
			memcpy(m_RecordData + m_TailPtr,(char *)InBuf,InSize);
		}
		else
		{
			memcpy(m_RecordData + m_TailPtr,(char *)InBuf,copysize);
			memcpy(m_RecordData,(char *)InBuf + copysize,InSize - copysize);
		}

		m_TailPtr = (m_TailPtr + InSize) % MSRVCOMM_LINK_SENDSIZE;
	}

	m_Parent->m_Parent->m_SendWaitEvent.ActiveEvent();

	m_Section.UnLock();

	return(InSize + sizeof(tagFrameHead));
}
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MSrvCommSendQueue,MObject)

END_LMYUNIT
//................................................................................................................................
MSrvCommSendQueue::MSrvCommSendQueue(void)
{
	m_Parent = NULL;
}
//................................................................................................................................
MSrvCommSendQueue::~MSrvCommSendQueue()
{
	Release();
}
//................................................................................................................................
int  MSrvCommSendQueue::Instance(MSrvCommSubUnit * Parent)
{
	register int					i;
	register int					errorcode;

	assert(Parent != NULL);

	Release();

	for ( i=0;i<=MSRVCOMM_UNIT_LINK_COUNT-1;i++ )
	{
		if ( (errorcode = m_RecordData[i].Instance(this)) < 0 )
		{
			Release();

			return(errorcode);
		}
	}

	m_Parent = Parent;

	return(1);
}
//................................................................................................................................
void MSrvCommSendQueue::Release(void)
{
	register int					i;

	for ( i=0;i<=MSRVCOMM_UNIT_LINK_COUNT-1;i++ )
	{
		m_RecordData[i].Release();
	}

	m_Parent = NULL;
}
//................................................................................................................................
int  MSrvCommSendQueue::GetSelectSocketInfo(tagSrvCommSelectLinkInfo * Out,unsigned short InSize)
{
	register int					i;
	register int					offset = 0;

	assert(m_Parent != NULL);

	for ( i=0;i<=MSRVCOMM_UNIT_LINK_COUNT-1;i++ )
	{
		Out[offset].Serial = i;
		if ( m_RecordData[i].IsEmpty(&Out[offset].LinkNo,&Out[offset].SocketId) == false )
		{
			offset ++;
		}
	}

	return(offset);
}
//................................................................................................................................
int  MSrvCommSendQueue::SendSocketData(unsigned short Serial,unsigned long LinkNo,SOCKET InSocket)
{
	assert(m_Parent != NULL);
	assert(Serial < MSRVCOMM_UNIT_LINK_COUNT);

	return(m_RecordData[Serial].SendSocketData(Serial,LinkNo,InSocket));
}
//................................................................................................................................
void MSrvCommSendQueue::Resert(unsigned short Serial,unsigned long LinkNo,SOCKET SocketId)
{
	assert(m_Parent != NULL);
	assert(Serial < MSRVCOMM_UNIT_LINK_COUNT);

	m_RecordData[Serial].Resert(LinkNo,SocketId);
}
//................................................................................................................................
int  MSrvCommSendQueue::SendFrame(unsigned long LinkNo,tagFrameHead * InHead,char * InBuf,unsigned short InSize)
{
	register unsigned int				no;
	register int						i;
	register int						errorcode = 0,sum = 0;

	if ( LinkNo != BROADCAST_LINK_NO )
	{
		no = MSRVCOMM_LINKORDER(LinkNo);
		assert(no < MSRVCOMM_UNIT_LINK_COUNT);

		return(m_RecordData[no].SendFrame(LinkNo,InHead,InBuf,InSize));
	}
	else
	{
		for ( i=0;i<=MSRVCOMM_UNIT_LINK_COUNT-1;i++ )
		{
			if ( (errorcode = m_RecordData[i].SendFrame(LinkNo,InHead,InBuf,InSize)) > 0 )
			{
				sum += errorcode;
			}
		}

		return(sum);
	}
}
//................................................................................................................................
int  MSrvCommSendQueue::CloseLink(unsigned long LinkNo)
{
	register unsigned int				no;

	no = MSRVCOMM_LINKORDER(LinkNo);
	assert(no < MSRVCOMM_UNIT_LINK_COUNT);

	return(m_RecordData[no].CloseLink(LinkNo));
}
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MSrvCommSubUnit,MObject)

END_LMYUNIT
//................................................................................................................................
MSrvCommSubUnit::MSrvCommSubUnit(void)
{

}
//................................................................................................................................
MSrvCommSubUnit::~MSrvCommSubUnit()
{
	Release();
}
//................................................................................................................................
void * __stdcall MSrvCommSubUnit::RecvThreadFun(void * In)
{
	register int						i;
	register MSrvCommSubUnit		*	classptr;
	tagSrvCommSelectLinkInfo			linkinfo[MSRVCOMM_UNIT_LINK_COUNT];
	register int						linkcount;
	fd_set								fdsetinfo;
	timeval								timeout;
	MCounter							refreshtimeout;
	long								maxselectno;

	assert(In != NULL);
	classptr = (MSrvCommSubUnit *)In;
	assert(classptr->m_Parent != NULL);
	refreshtimeout.GetCurTickCount();

	while ( classptr->m_Parent->m_StopCommThreadFlag == false )
	{
		try
		{
			classptr->m_RecvThread.RefreshThread();
			
			//30秒钟检查一次超时连接
			if ( refreshtimeout.GetDuration() >= 30000 )
			{
				classptr->m_LinkQueue.RefreshTimeOutLink();
				refreshtimeout.GetCurTickCount();
			}

			if ( (linkcount = classptr->m_LinkQueue.GetSelectSocketInfo(linkinfo,MSRVCOMM_UNIT_LINK_COUNT)) <= 0 )
			{
				classptr->m_RecvWaitEvent.WaitUntilActive(10);
				continue;
			}

			FD_ZERO(&fdsetinfo);

			maxselectno = 0;
			for ( i=0;i<=linkcount-1;i++ )
			{
				FD_SET(linkinfo[i].SocketId,&fdsetinfo);
				maxselectno = max(maxselectno,(long)(linkinfo[i].SocketId));
			}

			timeout.tv_sec = 0;
			timeout.tv_usec = 0;

			if ( select((int)(maxselectno + 1),&fdsetinfo,NULL,NULL,&timeout) <= 0 )
			{
				classptr->m_RecvWaitEvent.WaitUntilActive(10);
				continue;
			}

			for ( i=0;i<=linkcount-1;i++ )
			{
				if ( FD_ISSET(linkinfo[i].SocketId,&fdsetinfo) )
				{
					classptr->m_RecvTable.RecvSocketData(linkinfo[i].Serial,linkinfo[i].LinkNo,linkinfo[i].SocketId);
				}
			}
		}
		catch(...)
		{
			//接收客户端网络消息线程发生异常
			assert(0);
		}
	}

	return(0);
}
//................................................................................................................................
void * __stdcall MSrvCommSubUnit::SendThreadFun(void * In)
{
	register int						i;
	register MSrvCommSubUnit		*	classptr;
	tagSrvCommSelectLinkInfo			linkinfo[MSRVCOMM_UNIT_LINK_COUNT];
	register int						linkcount;
	fd_set								fdsetinfo;
	timeval								timeout;
	long								maxselectno;

	assert(In != NULL);
	classptr = (MSrvCommSubUnit *)In;
	assert(classptr->m_Parent != NULL);

	while ( classptr->m_Parent->m_StopCommThreadFlag == false )
	{
		try
		{
			classptr->m_SendThread.RefreshThread();

			if ( (linkcount = classptr->m_SendQueue.GetSelectSocketInfo(linkinfo,MSRVCOMM_UNIT_LINK_COUNT)) <= 0 )
			{
				classptr->m_SendWaitEvent.WaitUntilActive(10);
				continue;
			}
			
			FD_ZERO(&fdsetinfo);

			maxselectno = 0;
			for ( i=0;i<=linkcount-1;i++ )
			{
				FD_SET(linkinfo[i].SocketId,&fdsetinfo);
				maxselectno = max(maxselectno,(long)(linkinfo[i].SocketId));
			}

			timeout.tv_sec = 0;
			timeout.tv_usec = 0;

			if ( select((int)(maxselectno + 1),NULL,&fdsetinfo,NULL,&timeout) <= 0 )
			{
				classptr->m_SendWaitEvent.WaitUntilActive(10);
				continue;
			}

			for ( i=0;i<=linkcount-1;i++ )
			{
				if ( FD_ISSET(linkinfo[i].SocketId,&fdsetinfo) )
				{
					classptr->m_SendQueue.SendSocketData(linkinfo[i].Serial,linkinfo[i].LinkNo,linkinfo[i].SocketId);
				}
			}
		}
		catch(...)
		{
			//发送客户端网络消息发生异常
			assert(0);
		}
	}

	return(0);
}
//................................................................................................................................
int  MSrvCommSubUnit::Instance(unsigned short UnitSerial,MSrvCommUnit * Parent,unsigned long LinkTimeOut)
{
	register int					errorcode;
	char							tempbuf[32];

	assert(Parent != NULL);

	Release();

	m_UnitSerial = UnitSerial;
	m_Parent = Parent;

	if ( (errorcode = m_LinkQueue.Instance(this,LinkTimeOut)) < 0 )
	{
		Release();
		return(errorcode);
	}

	if ( (errorcode = m_RecvQueue.Instance(this)) < 0 )
	{
		Release();
		return(errorcode);
	}

	if ( (errorcode = m_RecvTable.Instance(this)) < 0 )
	{
		Release();
		return(errorcode);
	}

	if ( (errorcode = m_SendQueue.Instance(this)) < 0 )
	{
		Release();
		return(errorcode);
	}
	
	if ( (errorcode = m_RecvWaitEvent.Instance()) < 0 )
	{
		Release();
		return(errorcode);
	}

	if ( (errorcode = m_SendWaitEvent.Instance()) < 0 )
	{
		Release();
		return(errorcode);
	}

	_snprintf(tempbuf,32,"通讯单元接收线程[%d]",UnitSerial);
	if ( (errorcode = m_RecvThread.StartThread(tempbuf,RecvThreadFun,this)) < 0 )
	{
		Release();
		return(errorcode);
	}

	_snprintf(tempbuf,32,"通讯单元发送线程[%d]",UnitSerial);
	if ( (errorcode = m_SendThread.StartThread(tempbuf,SendThreadFun,this)) < 0 )
	{
		Release();
		return(errorcode);
	}

	return(1);
}
//................................................................................................................................
void MSrvCommSubUnit::Release(void)
{
	m_SendThread.StopThread();
	m_RecvThread.StopThread();

	m_RecvWaitEvent.Release();
	m_SendWaitEvent.Release();

	m_SendQueue.Release();
	m_RecvTable.Release();
	m_RecvQueue.Release();
	m_LinkQueue.Release();
}
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MSrvCommAcceptQueue,MObject)

END_LMYUNIT
//................................................................................................................................
MSrvCommAcceptQueue::MSrvCommAcceptQueue(void)
{
	m_RecordData = NULL;
	m_MaxRecord = 0;
}
//................................................................................................................................
MSrvCommAcceptQueue::~MSrvCommAcceptQueue()
{
	Release();
}
//................................................................................................................................
int  MSrvCommAcceptQueue::Instance(unsigned short MaxRecord)
{
	register int					i;

	Release();

	m_Section.Lock();

	m_RecordData = new tagSrvCommAcceptQueue[MaxRecord];
	if ( m_RecordData == NULL )
	{
		m_Section.UnLock();
		Release();

		return(ERROR_MSRVCOMMLINKQUEUE_NOMEMORY);
	}

	m_MaxRecord = MaxRecord;

	for ( i=0;i<=m_MaxRecord-1;i++ )
	{
		m_RecordData[i].LinkNo	= INVALID_LINK_NO;
		m_RecordData[i].SrvPort = 0xFFFF;
	}

	m_Section.UnLock();

	return(1);
}
//................................................................................................................................
void MSrvCommAcceptQueue::Release(void)
{
	register int					i;

	m_Section.Lock();

	if ( m_RecordData != NULL )
	{
		for ( i=0;i<=m_MaxRecord-1;i++ )
		{
			if ( m_RecordData[i].LinkNo != INVALID_LINK_NO )
			{
				::closesocket(m_RecordData[i].SocketId);
				m_RecordData[i].LinkNo = INVALID_LINK_NO;
				m_RecordData[i].SrvPort = 0xFFFF;	
			}
		}

		delete [] m_RecordData;
		m_RecordData = NULL;
	}
	m_MaxRecord = 0;

	m_Section.UnLock();
}
//................................................................................................................................
int  MSrvCommAcceptQueue::GetSelectSocketInfo(tagSrvCommAcceptQueue * Out,unsigned short InSize)
{
	register int					offset = 0;
	register int					i;

	assert(Out != NULL);
	assert(InSize >= m_MaxRecord);
	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);

	m_Section.Lock();

	for ( i=0;i<=m_MaxRecord-1;i++ )
	{
		if ( m_RecordData[i].LinkNo != INVALID_LINK_NO )
		{
			Out[offset].LinkNo		= m_RecordData[i].LinkNo;
			Out[offset].SocketId	= m_RecordData[i].SocketId;
			Out[offset].SrvPort		= m_RecordData[i].SrvPort;
			offset ++;
		}
	}

	m_Section.UnLock();

	return(offset);
}
//................................................................................................................................
int  MSrvCommAcceptQueue::CreateServerPort(unsigned short* pListenPort,unsigned long * LinkNo,unsigned short ListenQueueCount)
{
	register int						i;
	SOCKET								tempsocket;
	struct sockaddr_in					tempaddr;
	register unsigned long				linkno;
	register int						errorcode;
	unsigned int						bindoption = 1;

	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);

	m_Section.Lock();

	for ( i=0;i<m_MaxRecord;i++ )
	{
		if ( m_RecordData[i].LinkNo == INVALID_LINK_NO )
		{
			tempsocket = socket(AF_INET,SOCK_STREAM,0);
			if ( tempsocket == INVALID_SOCKET )
			{
				errorcode = ERROR_SYSTEM(WSAGetLastError());
				m_Section.UnLock();
				return(errorcode);
			}

			if ( MSocket::SetSocketAsync(tempsocket) < 0 )
			{
				errorcode = ERROR_SYSTEM(WSAGetLastError());
				m_Section.UnLock();
				closesocket(tempsocket);
				return(errorcode);
			}

			tempaddr.sin_family = AF_INET;
			tempaddr.sin_addr.s_addr = htonl(INADDR_ANY);
			tempaddr.sin_port = htons(pListenPort[i]);

			if ( bind(tempsocket,(sockaddr *)&tempaddr,sizeof(tempaddr)) == SOCKET_ERROR )
			{
				errorcode = ERROR_SYSTEM(WSAGetLastError());
				printf("绑定SOCKET失败，ErrorCode = %d\r\n",errorcode);
				m_Section.UnLock();
				closesocket(tempsocket);
				return(errorcode);
			}

			if ( listen(tempsocket,ListenQueueCount) == SOCKET_ERROR )
			{
				errorcode = ERROR_SYSTEM(WSAGetLastError());
				m_Section.UnLock();
				closesocket(tempsocket);
				return(errorcode);
			}

			linkno = 0xFFFF0000 + i;
			m_RecordData[i].LinkNo		= linkno;
			m_RecordData[i].SocketId	= tempsocket;
			m_RecordData[i].SrvPort		= pListenPort[i];

			if ( LinkNo != NULL )
				LinkNo[i] = linkno;
		}
	}

	m_Section.UnLock();

	return(1);
}
//................................................................................................................................
int  MSrvCommAcceptQueue::CloseServerLink(unsigned long LinkNo)
{
	register unsigned short				serial;

	assert(m_RecordData != NULL);
	serial = (unsigned short)(LinkNo & 0x0000FFFF);
	assert(serial < m_MaxRecord);

	m_Section.Lock();

	if ( m_RecordData[serial].LinkNo == LinkNo )
	{
		closesocket(m_RecordData[serial].SocketId);
		m_RecordData[serial].LinkNo		= INVALID_LINK_NO;
		m_RecordData[serial].SocketId	= INVALID_SOCKET;
		m_RecordData[serial].SrvPort	= 0xFFFF;

		m_Section.UnLock();

		return(1);
	}

	m_Section.UnLock();

	return(ERROR_MSRVCOMMLINKQUEUE_INVALIDLINK);
}
//--------------------------------------------------------------------------------------------------------------------------------
BEGIN_LMYUNIT(MSrvCommUnit,MObject)

END_LMYUNIT
//................................................................................................................................
MCriticalSection		MSrvCommUnit::staticSendSection;
//................................................................................................................................
unsigned long			MSrvCommUnit::staticSendSizeM = 0;
//................................................................................................................................
unsigned long			MSrvCommUnit::staticSendSizeB = 0;
//................................................................................................................................
MCounter				MSrvCommUnit::staticSendCounter;
//................................................................................................................................
unsigned long			MSrvCommUnit::staticOldSendSizeM = 0;
//................................................................................................................................
unsigned long			MSrvCommUnit::staticOldSendSizeB = 0;
//................................................................................................................................
MCriticalSection		MSrvCommUnit::staticRecvSection;
//................................................................................................................................
unsigned long			MSrvCommUnit::staticRecvSizeM = 0;
//................................................................................................................................
unsigned long			MSrvCommUnit::staticRecvSizeB = 0;
//................................................................................................................................
MCounter				MSrvCommUnit::staticRecvCounter;
//................................................................................................................................
unsigned long			MSrvCommUnit::staticOldRecvSizeM = 0;
//................................................................................................................................
unsigned long			MSrvCommUnit::staticOldRecvSizeB = 0;
//................................................................................................................................
unsigned long			MSrvCommUnit::staticLostRequestCount = 0;
//................................................................................................................................
unsigned long			MSrvCommUnit::staticLostSendCount = 0;
//................................................................................................................................
unsigned long			MSrvCommUnit::staticMustSendFrameCount = 0;
//................................................................................................................................
unsigned long			MSrvCommUnit::staticActulSendFrameCount = 0;
//................................................................................................................................
MCounter				MSrvCommUnit::staticSendFrameCounter;
//................................................................................................................................
void MSrvCommUnit::UpdateSendSize(unsigned short InSize)
{
	staticSendSection.Lock();

	staticSendSizeB += InSize;
	if ( staticSendSizeB >= (1024 * 1024) )
	{
		staticSendSizeM ++;
		staticSendSizeB = staticSendSizeB % (1024 * 1024);
	}

	if ( staticSendCounter.GetDuration() > MSRVCOMMUNIT_COMMBAND_TIME )
	{
		staticOldSendSizeM = staticSendSizeM;
		staticOldSendSizeB = staticSendSizeB;
		staticSendCounter.GetCurTickCount();
	}

	staticSendSection.UnLock();
}
//................................................................................................................................
void MSrvCommUnit::UpdateRecvSize(unsigned short InSize)
{
	staticRecvSection.Lock();

	staticRecvSizeB += InSize;
	if ( staticRecvSizeB >= (1024 * 1024) )
	{
		staticRecvSizeM ++;
		staticRecvSizeB = staticRecvSizeB % (1024 * 1024);
	}

	if ( staticRecvCounter.GetDuration() > MSRVCOMMUNIT_COMMBAND_TIME )
	{
		staticOldRecvSizeM = staticRecvSizeM;
		staticOldRecvSizeB = staticRecvSizeB;
		staticRecvCounter.GetCurTickCount();
	}

	staticRecvSection.UnLock();
}
//................................................................................................................................
MSrvCommUnit::MSrvCommUnit(void)
{
	m_RecordData = NULL;
	m_MaxRecord = 0;

	m_SelectSubUnit = 0;

	m_StopCommThreadFlag = false;

	m_LastSendBandWidth = 0;
	m_LastRecvBandWidth = 0;
}
//................................................................................................................................
MSrvCommUnit::~MSrvCommUnit()
{
	Release();
}
//................................................................................................................................
int  MSrvCommUnit::Instance(unsigned short MaxLinkCount, unsigned short ListenPortCnt ,unsigned long LinkTimeOut )
{
	register int							i;
	register int							errorcode;

	assert(MaxLinkCount != 0);

	Release();

	staticSendSection.Lock();

	staticSendSizeB = 0;
	staticSendSizeM = 0;
	staticSendCounter.GetCurTickCount();
	staticOldSendSizeM = 0;
	staticOldSendSizeB = 0;

	staticSendSection.UnLock();

	staticRecvSection.Lock();

	staticRecvSizeB = 0;
	staticRecvSizeM = 0;
	staticRecvCounter.GetCurTickCount();
	staticOldRecvSizeM = 0;
	staticOldRecvSizeB = 0;

	staticLostRequestCount = 0;
	staticLostSendCount = 0;

	m_LastSendBandWidth = 0;
	m_LastRecvBandWidth = 0;

	m_SelectSubUnit = 0;

	staticRecvSection.UnLock();

	staticMustSendFrameCount = 0;
	staticActulSendFrameCount = 0;
	
	if ( (errorcode = MSocket::InstanceCommCondition()) < 0 )
	{
		Release();
		return(errorcode);
	}

	m_StopCommThreadFlag = false;
	if ( MaxLinkCount % 64 == 0 )
	{
		m_MaxRecord = MaxLinkCount / 64;
	}
	else
	{
		m_MaxRecord = MaxLinkCount / 64 + 1;
	}

	m_RecordData = new MSrvCommSubUnit[m_MaxRecord];
	if ( m_RecordData == NULL )
	{
		Release();
		return(ERROR_MSRVCOMMLINKQUEUE_NOMEMORY);
	}

	for ( i=0;i<=m_MaxRecord-1;i++ )
	{
		if ( (errorcode = m_RecordData[i].Instance(i,this,LinkTimeOut)) < 0 )
		{
			Release();
			return(errorcode);
		}
	}

	if ( (errorcode = m_AcceptQueue.Instance( ListenPortCnt )) < 0 )
	{
		Release();
		return(errorcode);
	}

	if ( (errorcode = m_AcceptThread.StartThread("通讯单元Accept线程",AcceptThreadFun,this)) < 0 )
	{
		Release();
		return(errorcode);
	}

	return(1);
}
//................................................................................................................................
void MSrvCommUnit::Release(void)
{
	register int					i;

	m_StopCommThreadFlag = true;

	m_AcceptThread.StopThread();

	if ( m_RecordData != NULL )
	{
		for ( i=0;i<=m_MaxRecord-1;i++ )
		{
			m_RecordData[i].Release();
		}

		delete [] m_RecordData;
		m_RecordData = NULL;
	}
	m_MaxRecord = 0;

	m_AcceptQueue.Release();

	MSocket::ReleaseCommCondition();
}
//................................................................................................................................
int  MSrvCommUnit::SelectSubUnit(void)
{
	register int					i;
	register int					errorcode;

	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);

	for ( i=0;i<=m_MaxRecord-1;i++ )
	{
		errorcode = (m_SelectSubUnit + i) % m_MaxRecord;
		if ( m_RecordData[errorcode].m_LinkQueue.GetLinkCount() < MSRVCOMM_UNIT_LINK_COUNT )
		{
			m_SelectSubUnit ++;
			return(errorcode);
		}
	}

	return(0);
}
//................................................................................................................................
int  MSrvCommUnit::CreateServerPort(unsigned short* pListenPort,unsigned long * LinkNo,unsigned short ListenQueueCount)
{
	return(m_AcceptQueue.CreateServerPort(pListenPort,LinkNo,ListenQueueCount));
}
//................................................................................................................................
unsigned short MSrvCommUnit::GetLinkCount(void)
{
	register int						i;
	register unsigned short				errorcode = 0;

	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0);

	for ( i=0;i<=m_MaxRecord-1;i++ )
	{
		errorcode += m_RecordData[i].m_LinkQueue.GetLinkCount();
	}

	return(errorcode);
}
//................................................................................................................................
unsigned short MSrvCommUnit::GetUnitCount(void)
{
	return(m_MaxRecord);
}
//................................................................................................................................
int  MSrvCommUnit::Select(unsigned short UnitNo,tagSrvCommLinkMsgQueue * LinkMsg,tagSrvCommDataMsgQueue * DataMsg)
{
	assert(m_RecordData != NULL);
	assert(UnitNo < m_MaxRecord);
	assert(LinkMsg != NULL);
	assert(DataMsg != NULL);

	return(m_RecordData[UnitNo].m_RecvQueue.Select(LinkMsg,DataMsg));
}
//................................................................................................................................
int  MSrvCommUnit::RecvFrame(unsigned long LinkNo,tagFrameHead * OutHead,char * OutBuf,unsigned short InSize)
{
	register unsigned long				unitno;

	unitno = MSRVCOMM_LINKUNITNO(LinkNo);
	assert(m_RecordData != NULL);
	assert(unitno < m_MaxRecord);
	assert(OutHead != NULL);
	assert(OutBuf != NULL);

	return(m_RecordData[unitno].m_RecvQueue.RecvFrame(LinkNo,OutHead,OutBuf,InSize));
}
//................................................................................................................................
int  MSrvCommUnit::SendFrame(unsigned long LinkNo,tagFrameHead * InHead,char * InBuf,unsigned short InSize,int SendTimes)
{
	register unsigned long				unitno;
	register int						i;
	register int						errorcode = 0,sum = 0;
	register unsigned long				addtiondata;
	register int						returnerr;
	register int						sendtimes = 0;

	if ( SendTimes <= 0 )
	{
		SendTimes = MSRVCOMM_SEND_TIMES;
	}
	else if ( SendTimes > MSRVCOMM_SEND_TIMES )
	{
		SendTimes = MSRVCOMM_SEND_TIMES;
	}
	
	if ( m_RecordData == NULL || m_MaxRecord == 0 )
	{
		return(ERROR_MSRVCOMMLINKQUEUE_INVALIDLINK);
	}

	if ( LinkNo != BROADCAST_LINK_NO )
	{
		unitno = MSRVCOMM_LINKUNITNO(LinkNo);
		assert(unitno < m_MaxRecord);
		assert(InHead != NULL);

		staticMustSendFrameCount ++;
		staticActulSendFrameCount ++;

		while ( (returnerr = m_RecordData[unitno].m_SendQueue.SendFrame(LinkNo,InHead,InBuf,InSize)) < 0 )
		{
			if ( returnerr != ERROR_MSRVCOMMLINKQUEUE_SENDFULL )
			{
				return(returnerr);
			}

			sendtimes ++;
			staticActulSendFrameCount ++;

			if ( sendtimes < SendTimes )
			{
				MThread::Sleep(100);
			}
			else
			{
				break;
			}
		}

		return(returnerr);
	}
	else
	{
		for ( i=0;i<=m_MaxRecord-1;i++ )
		{
			addtiondata = 0;
			m_RecordData[i].m_LinkQueue.GetLinkAddtionData(i,LinkNo,&addtiondata);

			if ( addtiondata != 0 )
			{
				if ( (errorcode = m_RecordData[i].m_SendQueue.SendFrame(LinkNo,InHead,InBuf,InSize)) > 0 )
				{
					sum += errorcode;
				}
			}
		}

		return(sum);
	}
}
//................................................................................................................................
int  MSrvCommUnit::SendSocketFrame(SOCKET InSocket,tagFrameHead * InHead,char * InBuf,unsigned short InSize)
{
	MCRC16								crc;
	MLZW4096							lzw;
	char								tempbuf[MAX_FRAME_SIZE];
	register int						sendsize;
	register int						offset = 0;
	register int						errorcode;
	register int						sendtime = 0;

	if ( InSize > MAX_DATAFRAME_SIZE )
	{
		return(ERROR_MSRVCOMMLINKQUEUE_PARAM);
	}

	InHead->Market = '$';
	if ( InSize <= 100 )
	{
		InHead->DataSize = InSize;
		InHead->DataStatus = (InHead->DataStatus & 0x07) | 0x40;
		InHead->CheckCode = crc.CheckCode(InBuf,InSize);
		memcpy(tempbuf,(char *)InHead,sizeof(tagFrameHead));
		memcpy(tempbuf + sizeof(tagFrameHead),InBuf,InSize);
		sendsize = sizeof(tagFrameHead) + InSize;
	}
	else
	{
		if ( (errorcode = lzw.CompressBuf(InBuf,InSize,tempbuf + sizeof(tagFrameHead),MAX_DATAFRAME_SIZE)) < 0 )
		{
			InHead->DataSize = InSize;
			InHead->DataStatus = (InHead->DataStatus & 0x07) | 0x40;
			InHead->CheckCode = crc.CheckCode(InBuf,InSize);
			memcpy(tempbuf,(char *)InHead,sizeof(tagFrameHead));
			memcpy(tempbuf + sizeof(tagFrameHead),InBuf,InSize);
			sendsize = sizeof(tagFrameHead) + InSize;
		}
		else
		{
			InHead->DataSize = errorcode;
			InHead->DataStatus = (InHead->DataStatus & 0x07) | 0x48;
			InHead->CheckCode = crc.CheckCode(tempbuf + sizeof(tagFrameHead),errorcode);
			memcpy(tempbuf,(char *)InHead,sizeof(tagFrameHead));
			sendsize = sizeof(tagFrameHead) + errorcode;
		}
	}
	
	while ( offset < sendsize )
	{
#ifdef WINDOWSCODE
		if ( (errorcode = send(InSocket,tempbuf + offset,sendsize - offset,0)) == SOCKET_ERROR )
#else
		if ( (errorcode = send(InSocket,tempbuf + offset,sendsize - offset,MSG_NOSIGNAL)) == SOCKET_ERROR )
#endif
		{
			errorcode = WSAGetLastError();
			if ( errorcode != 10035 )
			{
				return(ERROR_SYSTEM(errorcode));
			}
		}

		offset += errorcode;
		sendtime ++;

		if ( sendtime >= 40 )
		{
			return(ERROR_MSRVCOMMLINKQUEUE_SENDTIMEOUT);
		}

		MThread::Sleep(50);
	}

	return(sendsize);
}
//................................................................................................................................
int  MSrvCommUnit::SendSocketBlockFrame(SOCKET InSocket,tagFrameHead * InHead,char * InBuf,unsigned short Offset,unsigned short BlockSize,unsigned short BlockCount)
{
	MCRC16								crc;
	MBlockDataCompress					block;
	char								tempbuf[MAX_FRAME_SIZE];
	register int						sendsize;
	register int						offset = 0;
	register int						errorcode;
	register int						sendtime = 0;

	if ( (errorcode = (Offset + BlockSize * BlockCount)) > MAX_DATAFRAME_SIZE )
	{
		return(ERROR_MSRVCOMMLINKQUEUE_PARAM);
	}

	if ( errorcode <= 100 )
	{
		InHead->DataSize = errorcode;
		InHead->DataStatus = (InHead->DataStatus & 0x07) | 0x40;
		InHead->CheckCode = crc.CheckCode(InBuf,errorcode);
		memcpy(tempbuf,(char *)InHead,sizeof(tagFrameHead));
		memcpy(tempbuf + sizeof(tagFrameHead),InBuf,errorcode);
		sendsize = sizeof(tagFrameHead) + errorcode;
	}
	else
	{
		if ( (errorcode = block.CompressBuf(InBuf,Offset,BlockSize,BlockCount,tempbuf + sizeof(tagFrameHead),MAX_DATAFRAME_SIZE)) < 0 )
		{
			errorcode = Offset + BlockSize * BlockCount;

			InHead->DataSize = errorcode;
			InHead->DataStatus = (InHead->DataStatus & 0x07) | 0x40;
			InHead->CheckCode = crc.CheckCode(InBuf,errorcode);
			memcpy(tempbuf,(char *)InHead,sizeof(tagFrameHead));
			memcpy(tempbuf + sizeof(tagFrameHead),InBuf,errorcode);
			sendsize = sizeof(tagFrameHead) + errorcode;
		}
		else
		{
			InHead->DataSize = errorcode;
			InHead->DataStatus = (InHead->DataStatus & 0x07) | 0x50;
			InHead->CheckCode = crc.CheckCode(tempbuf + sizeof(tagFrameHead),errorcode);
			memcpy(tempbuf,(char *)InHead,sizeof(tagFrameHead));
			sendsize = sizeof(tagFrameHead) + errorcode;
		}
	}

	while ( offset < sendsize )
	{
#ifdef WINDOWSCODE
		if ( (errorcode = send(InSocket,tempbuf + offset,sendsize - offset,0)) == SOCKET_ERROR )
#else
		if ( (errorcode = send(InSocket,tempbuf + offset,sendsize - offset,MSG_NOSIGNAL)) == SOCKET_ERROR )
#endif
		{
			errorcode = WSAGetLastError();
			if ( errorcode != 10035 )
			{
				return(ERROR_SYSTEM(errorcode));
			}
		}
		
		offset += errorcode;
		sendtime ++;
		
		if ( sendtime >= 40 )
		{
			return(ERROR_MSRVCOMMLINKQUEUE_SENDTIMEOUT);
		}
		
		MThread::Sleep(50);
	}
	
	return(sendsize);
}
//................................................................................................................................
int  MSrvCommUnit::RecvSocketFrameTemp(SOCKET InSocket,tagFrameHead * OutHead,char * OutBuf,unsigned short InSize)
{
	register int					errorcode;
	register int					recvsize;
	register int					recvtime;
	MCRC16							crc;

	recvsize = 0;
	recvtime = 0;
	while ( recvsize < sizeof(tagFrameHead) )
	{
		if ( recvtime >= 3 )
		{
			return(ERROR_MSRVCOMMLINKQUEUE_RECVTIMEOUT);
		}
#ifdef WINDOWSCODE
		if ( (errorcode = recv(InSocket,(char *)OutHead + recvsize,sizeof(tagFrameHead) - recvsize,0)) == SOCKET_ERROR )
#else
		if ( (errorcode = recv(InSocket,(char *)OutHead + recvsize,sizeof(tagFrameHead) - recvsize,MSG_NOSIGNAL)) == SOCKET_ERROR )			
#endif
		{
			return(ERROR_SYSTEM(WSAGetLastError()));
		}

		recvsize += errorcode;

		recvtime ++;
	}

	if ( OutHead->DataSize > InSize )
	{
		return(ERROR_MSRVCOMMLINKQUEUE_PARAMERROR);
	}

	recvsize = 0;
	recvtime = 0;
	while ( recvsize < OutHead->DataSize )
	{
		if ( recvtime >= 3 )
		{
			return(ERROR_MSRVCOMMLINKQUEUE_RECVTIMEOUT);
		}
#ifdef WINDOWSCODE
		if ( (errorcode = recv(InSocket,OutBuf + recvsize,OutHead->DataSize - recvsize,0)) == SOCKET_ERROR )
#else
		if ( (errorcode = recv(InSocket,OutBuf + recvsize,OutHead->DataSize - recvsize,MSG_NOSIGNAL)) == SOCKET_ERROR )
#endif
		{
			return(ERROR_SYSTEM(WSAGetLastError()));
		}

		recvsize += errorcode;

		recvtime ++;
	}

	if ( (OutHead->DataStatus & 0xC0) != 0 )
	{
		if ( crc.CheckCode(OutBuf,OutHead->DataSize) != OutHead->CheckCode )
		{
			return(ERROR_MSRVCOMMLINKQUEUE_CHECKCODE);
		}
	}

	return(OutHead->DataSize);
}
//................................................................................................................................
int  MSrvCommUnit::RecvSocketFrame(SOCKET InSocket,tagFrameHead * OutHead,char * OutBuf,unsigned short InSize)
{
	register int				recvsize;
	MLZW4096					lzwclass;
	MBlockDataCompress			blockclass;
	char						tempbuf[MAX_FRAME_SIZE];

	if ( (recvsize = MSrvCommUnit::RecvSocketFrameTemp(InSocket,OutHead,OutBuf,InSize)) < 0 )
	{
		return(recvsize);
	}

	//没有压缩
	if ( (OutHead->DataStatus & 0x38) == 0x00 )
	{
		return(recvsize);
	}
	//BlockCompress压缩
	else if ( (OutHead->DataStatus & 0x18) == 0x10 )
	{
		memcpy(tempbuf,OutBuf,recvsize);
		return(blockclass.ExpandBuf(tempbuf,recvsize,OutBuf,InSize));
	}
	//LZWCompress压缩
	else if ( (OutHead->DataStatus & 0x18) == 0x08 )
	{
		memcpy(tempbuf,OutBuf,recvsize);
		return(lzwclass.ExpandBuf(tempbuf,recvsize,OutBuf,InSize));
	}
	//未知压缩标记，头部描述错误
	else
	{
		return(ERROR_MSRVCOMMLINKQUEUE_FRAMEHEAD);
	}
}
//................................................................................................................................
int  MSrvCommUnit::CloseLink(unsigned long LinkNo,bool Immidately)
{
	register unsigned short				unitno;
	register unsigned short				serial;

	assert(m_RecordData != NULL);
	unitno = MSRVCOMM_LINKUNITNO(LinkNo);
	if ( unitno == 0xFFFF )
	{
		return(m_AcceptQueue.CloseServerLink(LinkNo));
	}
	else
	{
		assert(unitno < m_MaxRecord);
		serial = MSRVCOMM_LINKORDER(LinkNo);
		if ( Immidately == true )
		{
			return(m_RecordData[unitno].m_LinkQueue.CloseLink(serial,LinkNo,MSRVCOMM_CLOSETYPE_SRV));
		}
		else
		{
			return(m_RecordData[unitno].m_SendQueue.CloseLink(LinkNo));
		}
	}
}
//................................................................................................................................
int  MSrvCommUnit::SetLinkAddtionData(unsigned long LinkNo,unsigned long AddtionData)
{
	register unsigned short				unitno;
	register unsigned short				serial;

	assert(m_RecordData != NULL);
	unitno = MSRVCOMM_LINKUNITNO(LinkNo);
	assert(unitno < m_MaxRecord);
	serial = MSRVCOMM_LINKORDER(LinkNo);

	return(m_RecordData[unitno].m_LinkQueue.SetLinkAddtionData(serial,LinkNo,AddtionData));
}
//................................................................................................................................
int  MSrvCommUnit::GetLinkAddtionData(unsigned long LinkNo,unsigned long * AddtionData)
{
	register unsigned short				unitno;
	register unsigned short				serial;

	assert(m_RecordData != NULL);
	unitno = MSRVCOMM_LINKUNITNO(LinkNo);
	assert(unitno < m_MaxRecord);
	serial = MSRVCOMM_LINKORDER(LinkNo);

	return(m_RecordData[unitno].m_LinkQueue.GetLinkAddtionData(serial,LinkNo,AddtionData));
}
//................................................................................................................................
int  MSrvCommUnit::GetLinkUnitInfo(unsigned short UnitNo,tagSrvCommLinkQueue * Out,unsigned short InSize)
{
	assert(UnitNo < m_MaxRecord);

	return(m_RecordData[UnitNo].m_LinkQueue.GetLinkUnitInfo(Out,InSize));
}
//................................................................................................................................
int  MSrvCommUnit::GetLinkInfo(unsigned long LinkNo,tagSrvCommLinkQueue * Out)
{
	register unsigned short				unitno;
	register unsigned short				serial;

	unitno = MSRVCOMM_LINKUNITNO(LinkNo);
	assert(unitno < m_MaxRecord);
	serial = MSRVCOMM_LINKORDER(LinkNo);

	return(m_RecordData[unitno].m_LinkQueue.GetLinkInfo(serial,LinkNo,Out));
}
//................................................................................................................................
bool MSrvCommUnit::VerifyIP(char * IPAddr)
{
	return(true);
}
//................................................................................................................................
float MSrvCommUnit::GetSendAmount(void)
{
	register float					errorcode;

	staticSendSection.Lock();

	errorcode = (float)staticSendSizeM * 1024 * 1024 + (float)staticSendSizeB;

	staticSendSection.UnLock();

	return(errorcode);
}
//................................................................................................................................
float MSrvCommUnit::GetRecvAmount(void)
{
	register float					errorcode;

	staticRecvSection.Lock();

	errorcode = (float)staticRecvSizeM * 1024 * 1024 + (float)staticRecvSizeB;

	staticRecvSection.UnLock();

	return(errorcode);
}
//................................................................................................................................
unsigned long MSrvCommUnit::GetSendCommBand(void)
{
	double					errorcode;

	staticSendSection.Lock();

	errorcode = ((double)(staticSendSizeM - staticOldSendSizeM) * 1024 * 1024 + staticSendSizeB - staticOldSendSizeB) * 8000;
	if ( staticSendCounter.GetDuration() < (MSRVCOMMUNIT_COMMBAND_TIME / 2) && m_LastSendBandWidth != 0 )
	{
		errorcode = ((double)m_LastSendBandWidth * MSRVCOMMUNIT_COMMBAND_TIME + errorcode) / (MSRVCOMMUNIT_COMMBAND_TIME + staticSendCounter.GetDuration());
	}
	else
	{
		errorcode = errorcode / (staticSendCounter.GetDuration() + 1);
	}

	if ( staticSendCounter.GetDuration() > MSRVCOMMUNIT_COMMBAND_TIME )
	{
		staticOldSendSizeM = staticSendSizeM;
		staticOldSendSizeB = staticSendSizeB;
		staticSendCounter.GetCurTickCount();
	}

	m_LastSendBandWidth = (unsigned long)errorcode;

	staticSendSection.UnLock();

	return((unsigned long)errorcode);
}
//................................................................................................................................
unsigned long MSrvCommUnit::GetRecvCommBand(void)
{
	double					errorcode;

	staticRecvSection.Lock();

	errorcode = ((double)(staticRecvSizeM - staticOldRecvSizeM) * 1024 * 1024 + staticRecvSizeB - staticOldRecvSizeB) * 8000;
	if ( staticRecvCounter.GetDuration() < (MSRVCOMMUNIT_COMMBAND_TIME / 2) && m_LastRecvBandWidth != 0 )
	{
		errorcode = ((double)m_LastRecvBandWidth * MSRVCOMMUNIT_COMMBAND_TIME + errorcode) / (MSRVCOMMUNIT_COMMBAND_TIME + staticRecvCounter.GetDuration());
	}
	else
	{
		errorcode = errorcode / (staticRecvCounter.GetDuration() + 1);
	}

	if ( staticRecvCounter.GetDuration() > MSRVCOMMUNIT_COMMBAND_TIME )
	{
		staticOldRecvSizeM = staticRecvSizeM;
		staticOldRecvSizeB = staticRecvSizeB;
		staticRecvCounter.GetCurTickCount();
	}

	m_LastRecvBandWidth = (unsigned long)errorcode;

	staticRecvSection.UnLock();

	return((unsigned long)errorcode);
}
//................................................................................................................................
float MSrvCommUnit::GetCommSendFluxValue(void)
{
	float					errorcode;

	errorcode = (float)staticActulSendFrameCount / (staticMustSendFrameCount + 1);
	if ( staticSendFrameCounter.GetDuration() >= 60000 )
	{
		staticActulSendFrameCount = 0;
		staticMustSendFrameCount = 0;

		staticSendFrameCounter.GetCurTickCount();
	}

	return(errorcode);
}
//................................................................................................................................
unsigned long MSrvCommUnit::GetWaitRequestCount(void)
{
	register int						i;
	register unsigned long				errorcode = 0;

	assert(m_RecordData != NULL);
	assert(m_MaxRecord != 0 );

	for ( i=0;i<=m_MaxRecord-1;i++ )
	{
		errorcode += m_RecordData[i].m_RecvQueue.GetWaitRequestCount();
	}

	return(errorcode);
}
//................................................................................................................................
void * __stdcall MSrvCommUnit::AcceptThreadFun(void * In)
{
	MSrvCommUnit					*	classptr;
	fd_set								fdsetinfo;
	timeval								timeout;
	tagSrvCommAcceptQueue				linkinfo[MSRVCOMM_MAX_ACCEPT_COUNT];
	register int						linkcount;
	register int						i;
	SOCKET								tempsocket;
	struct sockaddr_in					tempaddr;
	int									templength;
	register int						subunitno;
	char								ipaddr[16];
	long								maxselectno;

	assert(In != NULL);
	classptr = (MSrvCommUnit *)In;

	while ( classptr->m_StopCommThreadFlag == false )
	{
		try
		{
			classptr->m_AcceptThread.RefreshThread();

			if ( (linkcount = classptr->m_AcceptQueue.GetSelectSocketInfo(linkinfo,MSRVCOMM_MAX_ACCEPT_COUNT)) <= 0 )
			{
				MThread::Sleep(50);
				continue;
			}

			FD_ZERO(&fdsetinfo);

			maxselectno = 0;
			for ( i=0;i<=linkcount-1;i++ )
			{
				FD_SET(linkinfo[i].SocketId,&fdsetinfo);
				maxselectno = max((long)(linkinfo[i].SocketId),maxselectno);
			}

			timeout.tv_sec = 1;
			timeout.tv_usec = 0;

			if ( select((int)(maxselectno + 1),&fdsetinfo,NULL,NULL,&timeout) <= 0 )
			{
				MThread::Sleep(50);
				continue;
			}

			for ( i=0;i<=linkcount-1;i++ )
			{
				if ( FD_ISSET(linkinfo[i].SocketId,&fdsetinfo) )
				{
					templength = sizeof(sockaddr_in);
#ifdef WINDOWSCODE
					tempsocket = accept(linkinfo[i].SocketId,(sockaddr *)&tempaddr,&templength);
#else
					tempsocket = accept(linkinfo[i].SocketId,(sockaddr *)&tempaddr,(socklen_t *)&templength);
#endif //WINDOWSCODE
					if ( tempsocket != INVALID_SOCKET )
					{
						//判断该IP地址是否允许使用
						strncpy(ipaddr,inet_ntoa(tempaddr.sin_addr),16);

						if ( classptr->VerifyIP(ipaddr) == false )
						{
							//该IP不允许被连接
							closesocket(tempsocket);
							continue;
						}

						MSocket::SetSocketAsync(tempsocket);

						if ( (subunitno = classptr->SelectSubUnit()) < 0 )
						{
							closesocket(tempsocket);
							continue;
						}
						else
						{
							if ( classptr->m_RecordData[subunitno].m_LinkQueue.AddLinkCount(	tempsocket,
																								linkinfo[i].LinkNo,
																								ipaddr,
																								tempaddr.sin_port,
																								linkinfo[i].SrvPort,
																								MSRVCOMM_LINKTYPE_ACCEPT	) == INVALID_LINK_NO )
							{
								closesocket(tempsocket);
								continue;
							}
						}
					}
				}
			}
		}
		catch(...)
		{
			//接收客户端连接线程发生异常
			assert(0);
		}
	}

	return(0);
}
//--------------------------------------------------------------------------------------------------------------------------------
