//--------------------------------------------------------------------------------------------------------------------------------
//                  ;;;,
//        ,;;;;;: ,;;;:.,;..
//         :;;"`,;;;;;;"":;;					单元名称：服务器端通讯处理
//      ..;;:  .;;,.;;:',;;"
//    ,;;;;;;" :;`',;",;;"						编写日期：2004年5月20
//   :" ,;:` , `:.;;;;;'
//    ,;;;,;:;;,;;;, ,;							编写人员：richtech
//   :;;;"` `:;;;;;,;,.;.
//   '""   .;;`.;";:;;;;` ;,					备注信息：
//       .;"`  ::. '   .,;;;
//      ""     ';;;;;;;;;;`
//--------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMSrvCommH__
#define __LmyUnitMSrvCommH__
//--------------------------------------------------------------------------------------------------------------------------------
//公共头文件
#include "mmutex.h"
#include "mobject.h"
#include "mdatetime.h"
#include "mdatastruct.h"
#include "mthread.h"
#include "mcheckcode.h"
#include "mlzw.h"
#include "mblockcompress.h"
#include "msocket.h"
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
//--------------------------------------------------------------------------------------------------------------------------------
class MSrvCommLinkQueue;
class MSrvCommRecvQueue;
class MSrvCommSendQueue;
class MSrvCommSubUnit;
class MSrvCommUnit;
//--------------------------------------------------------------------------------------------------------------------------------
#define MAX_FRAME_SIZE				4096					//每个消息包最大长度（含消息头部）
#define MAX_DATAFRAME_SIZE			(MAX_FRAME_SIZE - sizeof(tagFrameHead))
#define MAX_COMMDATAFRAME_SIZE		4000
#define INVALID_LINK_NO				0xFFFFFFFF				//无效连接
#define BROADCAST_LINK_NO			0xFFFFFFFE				//广播连接
//................................................................................................................................
#define MSRVCOMM_UNIT_LINK_COUNT	64						//连接单元中的连接数量
#define MSRVCOMM_MAX_ACCEPT_COUNT	64						//最大服务的端口数量
#define MSRVCOMM_TIMEOUT			60000					//超时时间
#define MSRVCOMM_LINK_RECVSIZE		4150					//每个连接的接收缓冲大小
#define MSRVCOMM_LINK_RECVCOUNT		20						//给个连接最大请求数量
#define MSRVCOMM_LINK_SENDSIZE		122880					//每个连接的发送缓冲大小
#define MSRVCOMM_SEND_TIMES			3						//发送数据包次数[每一次休息100毫秒]
//................................................................................................................................
#define	MSRVCOMMUNIT_COMMBAND_TIME	10000					//带宽统计时间（即最近多少毫秒内的带宽统计）
//................................................................................................................................
#define		MSRVCOMM_LINKORDER(linkno)			((unsigned short)(((linkno) & 0x0000FFFF) / 1000))
#define		MSRVCOMM_LINKUNITNO(linkno)			((unsigned short)(((linkno) & 0xFFFF0000) >> 16 ))
//--------------------------------------------------------------------------------------------------------------------------------
//网络消息定义 = 网络消息头部 + 网络消息内容
typedef struct
{
	char	                        Market;					//同步标记，为'$'
    unsigned char	                MainType;				//帧类型
	unsigned char	                ChildType;				//子类型
    unsigned short                  FrameCount;				//连续数据包数量
    unsigned short                  FrameNo;				//连续数据包编号（从0开始编号）
    unsigned short                  DataSize;				//数据长度（不包含数据包头部）
    unsigned char                   DataStatus;				//数据状态（包含压缩、加密）
    unsigned short                  ErrorCode;				//数据包返回码
    unsigned short                  CheckCode;				//数据包头部校验码
    unsigned short                  RequestCode;			//请求编号
	unsigned char					DCDStatus;				//DCD状态(仅2.X协议有效)
															//0 盘中
															//1 初始化
															//2 休市
															//3 盘后
	unsigned short					DCDTime;				//DCD时间(HH * 60 + MM格式)
	unsigned char                   Reserved[1];			//保留字节(在LinBox系统中,这个字节表示当前上海市场的时间点)
} tagFrameHead;
//................................................................................................................................
typedef struct
{
	unsigned long					LinkNo;					//连接号
	unsigned long					ParentNo;				//父连接号
	SOCKET							SocketId;				//相关的SOCKET
	char							IPAddr[16];				//IP地址
	unsigned long					Port;					//客户端端口号
	unsigned long					LinkType;				//连接类型
	MCounter						LinkTime;				//连接时间
	unsigned long					RecvSize;				//接收字节
	MCounter						RecvTime;				//最后一次接收时间
	unsigned long					SendSize;				//发送字节
	MCounter						SendTime;				//发送时间
	unsigned long					OrderRecord;			//连接顺序纪录
	unsigned long					AddtionData;			//附加数据[现在作为连接类型]
	unsigned short					SrvPort;				//服务端口号
	char							Reserved[8];			//保留
} tagSrvCommLinkQueue;
//................................................................................................................................
enum														//连接类型
{
	MSRVCOMM_LINKTYPE_ACCEPT = 0,							//客户端主动连接服务器，服务器Accept的连接
	MSRVCOMM_LINKTYPE_NOCONNECT = 128,						//服务器主动连接客户端，但没有调用Connect的连接
	MSRVCOMM_LINKTYPE_CONNECT,								//服务器主动连接客户端，调用Connect的连接，但不知连接是否成功
	MSRVCOMM_LINKTYPE_LINKSUC,								//服务器主动连接客户端，调用Connect的连接，且连接成功
};
//................................................................................................................................
enum														//关闭类型
{
	MSRVCOMM_CLOSETYPE_SRV = 0,								//服务器主动关闭
	MSRVCOMM_CLOSETYPE_CLIENT,								//客户端主动关闭
	MSRVCOMM_CLOSETYPE_RECV,								//接收数据包错误
	MSRVCOMM_CLOSETYPE_SEND,								//发送数据包错误
	MSRVCOMM_CLOSETYPE_TIMEOUT,								//超时关闭
};
//................................................................................................................................
typedef struct
{
	unsigned short					Serial;					//序号
	unsigned long					LinkNo;					//连接号
	SOCKET							SocketId;				//SOCKET
} tagSrvCommSelectLinkInfo;
//................................................................................................................................
typedef struct
{
	unsigned char					MsgType;
	unsigned long					LinkNo;
	unsigned long					ParentNo;
	char							IPAddr[16];
	unsigned long					Port;
	unsigned long					LinkType;
	unsigned long					AddtionData;
	unsigned char					CloseType;
} tagSrvCommLinkMsg;
//................................................................................................................................
enum
{
	MSRVCOMM_LINKMSG_ADD = 0,		//添加连接
	MSRVCOMM_LINKMSG_CLOSE,			//关闭连接
};
//................................................................................................................................
typedef struct
{
	tagSrvCommLinkMsg				LinkMsg[MSRVCOMM_UNIT_LINK_COUNT];
	unsigned short					LinkCount;
} tagSrvCommLinkMsgQueue;
//................................................................................................................................
typedef struct
{
	unsigned long					LinkNo[MSRVCOMM_UNIT_LINK_COUNT];
	unsigned short					LinkCount;
} tagSrvCommDataMsgQueue;
//................................................................................................................................
typedef struct
{
	unsigned long					LinkNo;
	char							RecvBuf[MAX_FRAME_SIZE];
	unsigned short					RecvSize;
} tagSrvCommRecvTable;
//................................................................................................................................
typedef struct
{
	unsigned long					LinkNo;
	SOCKET							SocketId;
	unsigned short					SrvPort;
} tagSrvCommAcceptQueue;
//--------------------------------------------------------------------------------------------------------------------------------
#define		ERROR_MSRVCOMMLINKQUEUE_INVALIDLINK		(ERROR_USER(140))		//执行通讯单元函数发生错误[无效的连接号]
#define		ERROR_MSRVCOMMLINKQUEUE_NODATA			(ERROR_USER(141))		//执行通讯单元函数发生错误[没有匹配的数据]
#define		ERROR_MSRVCOMMLINKQUEUE_FRAMEHEAD		(ERROR_USER(142))		//通讯单元接收数据包发生错误[数据包头部错误]
#define		ERROR_MSRVCOMMLINKQUEUE_SENDFULL		(ERROR_USER(143))		//通讯单元发送数据包发生错误[缓冲区已满]
#define		ERROR_MSRVCOMMLINKQUEUE_NOMEMORY		(ERROR_USER(144))		//通讯单元初始化发生错误[没有足够的内存可以分配]
#define		ERROR_MSRVCOMMLINKQUEUE_SRVPORT			(ERROR_USER(145))		//通讯单元创建服务端口发生错误[缓冲区已满]
#define		ERROR_MSRVCOMMLINKQUEUE_SENDTIMEOUT		(ERROR_USER(146))		//发送SOCKET数据超时
#define		ERROR_MSRVCOMMLINKQUEUE_RECVTIMEOUT		(ERROR_USER(147))		//接收SOCKET数据超时
#define		ERROR_MSRVCOMMLINKQUEUE_PARAMERROR		(ERROR_USER(148))		//接收SOCKET数据参数错误
#define		ERROR_MSRVCOMMLINKQUEUE_CHECKCODE		(ERROR_USER(149))		//接收SOCKET数据校验错误
#define		ERROR_MSRVCOMMLINKQUEUE_PARAM			(ERROR_USER(150))		//发送或接收SOCKET数据参数错误
//................................................................................................................................
class MSrvCommLinkQueue : public MObject
{
protected:
	MCriticalSection				m_Section;
	tagSrvCommLinkQueue				m_RecordData[MSRVCOMM_UNIT_LINK_COUNT];
	unsigned short					m_RecordCount;
	MResourceRecordSt				m_FreeRecord;
	MSrvCommSubUnit				*	m_Parent;
	unsigned long					m_LinkTimeOut;
public:
	MSrvCommLinkQueue(void);
	virtual ~MSrvCommLinkQueue();
public:
	int  Instance(MSrvCommSubUnit * Parent,unsigned long LinkTimeOut);
	void Release(void);
public:
	int  GetSelectSocketInfo(tagSrvCommSelectLinkInfo * Out,unsigned short InSize = MSRVCOMM_UNIT_LINK_COUNT);
	int  GetLinkUnitInfo(tagSrvCommLinkQueue * Out,unsigned short InSize = MSRVCOMM_UNIT_LINK_COUNT);
	int  GetLinkInfo(unsigned short Serial,unsigned long LinkNo,tagSrvCommLinkQueue * Out);
public:
	unsigned long AddLinkCount(SOCKET SocketId,unsigned long ParentNo,char * IPAddr,unsigned long Port, unsigned short SrvPort, unsigned long LinkType);
	int  CloseLink(unsigned short Serial,unsigned long LinkNo,unsigned char CloseType);
public:
	unsigned short GetLinkCount(void);
public:
	int  UpdateRecvInfo(unsigned short Serial,unsigned long LinkNo,unsigned short In);
	int  UpdateSendInfo(unsigned short Serial,unsigned long LinkNo,unsigned short In);
public:
	void RefreshTimeOutLink(void);
public:
	int  SetLinkAddtionData(unsigned short Serial,unsigned long LinkNo,unsigned long AddtionData);
	int  GetLinkAddtionData(unsigned short Serial,unsigned long LinkNo,unsigned long * AddtionData);

	DECLARE_LMYUNIT(MSrvCommLinkQueue)
};
//................................................................................................................................
class MSrvCommRecvGroup : public MObject
{
protected:
	MCriticalSection				m_Section;
	MCharLoopGroupSt				m_RecordData;
	unsigned long					m_LinkNo;
	unsigned short					m_WaitRequestCount;
public:
	MSrvCommRecvGroup(void);
	virtual ~MSrvCommRecvGroup();
public:
	int  Instance(void);
	void Release(void);
public:
	int  PutData(unsigned long LinkNo,char * InBuf,unsigned short InSize);
	int  GetData(unsigned long LinkNo,tagFrameHead * OutHead,char * OutBuf,unsigned short InSize);
public:
	void Resert(unsigned long LinkNo);
	bool IsEmpty(unsigned long * LinkNo);
	unsigned short GetWaitRequestCount(void);

	DECLARE_LMYUNIT(MSrvCommRecvGroup)
};
//................................................................................................................................
class MSrvCommRecvQueue : public MObject
{
protected:
	MSrvCommRecvGroup					m_RecordData[MSRVCOMM_UNIT_LINK_COUNT];
	MLoopGroupMt<tagSrvCommLinkMsg>		m_MsgRecord;
	MWaitEvent							m_WaitEvent;
public:
	MSrvCommRecvQueue(void);
	virtual ~MSrvCommRecvQueue();
public:
	int  Instance(MSrvCommSubUnit * Parent);
	void Release(void);
public:
	int  PutData(unsigned short Serial,unsigned long LinkNo,char * InBuf,unsigned short InSize);
	int  RecvFrame(unsigned long LinkNo,tagFrameHead * OutHead,char * OutBuf,unsigned short InSize);
public:
	int  AddLinkMsg(tagSrvCommLinkMsg * Msg);
public:
	void Resert(unsigned short Serial,unsigned long LinkNo);
public:
	int  Select(tagSrvCommLinkMsgQueue * LinkMsg,tagSrvCommDataMsgQueue * DataMsg);
public:
	unsigned short GetWaitRequestCount(void);

	DECLARE_LMYUNIT(MSrvCommRecvQueue)
};
//................................................................................................................................
class MSrvCommRecvTable : public MObject
{
protected:
	MCriticalSection				m_Section;
	tagSrvCommRecvTable				m_RecordData[MSRVCOMM_UNIT_LINK_COUNT];
	MSrvCommSubUnit				*	m_Parent;
public:
	MSrvCommRecvTable(void);
	virtual ~MSrvCommRecvTable();
public:
	int  Instance(MSrvCommSubUnit * Parent);
	void Release(void);
public:
	int  RecvSocketData(unsigned short Serial,unsigned long LinkNo,SOCKET InSocket);
	void Resert(unsigned short Serial,unsigned long LinkNo);

	DECLARE_LMYUNIT(MSrvCommRecvTable)
};
//................................................................................................................................
class MSrvCommSendGroup : public MObject
{
protected:
	MCriticalSection				m_Section;
	char							m_RecordData[MSRVCOMM_LINK_SENDSIZE];
	unsigned long					m_HeadPtr;
	unsigned long					m_TailPtr;
	unsigned long					m_LinkNo;
	SOCKET							m_SocketId;
	bool							m_CloseFlag;
	MSrvCommSendQueue			*	m_Parent;
public:
	MSrvCommSendGroup(void);
	virtual ~MSrvCommSendGroup();
public:
	int  Instance(MSrvCommSendQueue * Parent);
	void Release(void);
public:
	int  SendSocketData(unsigned short Serial,unsigned long LinkNo,SOCKET InSocket);
	bool IsEmpty(unsigned long * LinkNo,SOCKET * SocketId);
	void Resert(unsigned long LinkNo,SOCKET SocketId);
public:
	int  SendFrame(unsigned long LinkNo,tagFrameHead * InHead,char * InBuf,unsigned short InSize);
	int  CloseLink(unsigned long LinkNo);

	DECLARE_LMYUNIT(MSrvCommSendGroup)
};
//................................................................................................................................
class MSrvCommSendQueue : public MObject
{
friend class MSrvCommSendGroup;
protected:
	MSrvCommSendGroup				m_RecordData[MSRVCOMM_UNIT_LINK_COUNT];
	MSrvCommSubUnit				*	m_Parent;
public:
	MSrvCommSendQueue(void);
	virtual ~MSrvCommSendQueue();
public:
	int  Instance(MSrvCommSubUnit * Parent);
	void Release(void);
public:
	int  GetSelectSocketInfo(tagSrvCommSelectLinkInfo * Out,unsigned short InSize = MSRVCOMM_UNIT_LINK_COUNT);
	int  SendSocketData(unsigned short Serial,unsigned long LinkNo,SOCKET InSocket);
public:
	void Resert(unsigned short Serial,unsigned long LinkNo,SOCKET SocketId);
public:
	int  SendFrame(unsigned long LinkNo,tagFrameHead * InHead,char * InBuf,unsigned short InSize);
	int  CloseLink(unsigned long LinkNo);

	DECLARE_LMYUNIT(MSrvCommSendQueue)
};
//................................................................................................................................
class MSrvCommSubUnit : public MObject
{

friend class MSrvCommLinkQueue;
friend class MSrvCommRecvTable;
friend class MSrvCommSendGroup;
friend class MSrvCommUnit;

protected:
	MSrvCommLinkQueue				m_LinkQueue;
	MSrvCommRecvQueue				m_RecvQueue;
	MSrvCommRecvTable				m_RecvTable;
	MSrvCommSendQueue				m_SendQueue;
protected:
	unsigned short					m_UnitSerial;
	MSrvCommUnit				*	m_Parent;
protected:
	MThread							m_RecvThread;
	MThread							m_SendThread;
protected:
	MWaitEvent						m_RecvWaitEvent;
	MWaitEvent						m_SendWaitEvent;
protected:
	static void * __stdcall RecvThreadFun(void * In);
	static void * __stdcall SendThreadFun(void * In);
public:
	MSrvCommSubUnit(void);
	virtual ~MSrvCommSubUnit();
public:
	int  Instance(unsigned short UnitSerial,MSrvCommUnit * Parent,unsigned long LinkTimeOut);
	void Release(void);

	DECLARE_LMYUNIT(MSrvCommSubUnit)
};
//................................................................................................................................
class MSrvCommAcceptQueue : public MObject
{
protected:
	MCriticalSection				m_Section;
	tagSrvCommAcceptQueue		*	m_RecordData;
	unsigned short					m_MaxRecord;
public:
	MSrvCommAcceptQueue(void);
	virtual ~MSrvCommAcceptQueue();
public:
	int  Instance(unsigned short MaxRecord);
	void Release(void);
public:
	int  GetSelectSocketInfo(tagSrvCommAcceptQueue * Out,unsigned short InSize = MSRVCOMM_MAX_ACCEPT_COUNT);
public:
	int  CreateServerPort(unsigned short* pListenPort,unsigned long * LinkNo,unsigned short ListenQueueCount);
	int  CloseServerLink(unsigned long LinkNo);

	DECLARE_LMYUNIT(MSrvCommAcceptQueue)
};
//................................................................................................................................
class MSrvCommUnit : public MObject
{

friend class MSrvCommSubUnit;
friend class MSrvCommSendGroup;
friend class MSrvCommRecvTable;
friend class MSrvCommRecvGroup;

protected:
	static MCriticalSection			staticSendSection;
	static unsigned long			staticSendSizeM;
	static unsigned long			staticSendSizeB;
	static MCounter					staticSendCounter;
	static unsigned long			staticOldSendSizeM;
	static unsigned long			staticOldSendSizeB;
protected:
	static MCriticalSection			staticRecvSection;
	static unsigned long			staticRecvSizeM;
	static unsigned long			staticRecvSizeB;
	static MCounter					staticRecvCounter;
	static unsigned long			staticOldRecvSizeM;
	static unsigned long			staticOldRecvSizeB;
protected:
	static unsigned long			staticLostRequestCount;
	static unsigned long			staticLostSendCount;
protected:
	static unsigned long			staticMustSendFrameCount;
	static unsigned long			staticActulSendFrameCount;
	static MCounter					staticSendFrameCounter;
protected:
	static void UpdateSendSize(unsigned short InSize);
	static void UpdateRecvSize(unsigned short InSize);
protected:
	unsigned long					m_LastSendBandWidth;
	unsigned long					m_LastRecvBandWidth;
protected:
	MSrvCommSubUnit				*	m_RecordData;
	unsigned short					m_MaxRecord;
protected:
	MSrvCommAcceptQueue				m_AcceptQueue;
	MThread							m_AcceptThread;
public:
	unsigned short					m_SelectSubUnit;
protected:
	__inline int  SelectSubUnit(void);
	static void * __stdcall AcceptThreadFun(void * In);
protected:
	bool							m_StopCommThreadFlag;
public:
	MSrvCommUnit(void);
	virtual ~MSrvCommUnit();
public:
	virtual int  Instance(unsigned short MaxLinkCount, unsigned short ListenPortCnt ,unsigned long LinkTimeOut = 60);
	virtual void Release(void);
public:
	virtual int  CreateServerPort(unsigned short* pListenPort, unsigned long * LinkNo,unsigned short ListenQueueCount = 100);
	virtual int  CloseLink(unsigned long LinkNo,bool Immidately = false);
public:
	virtual unsigned short GetLinkCount(void);
	virtual unsigned short GetUnitCount(void);
public:
	virtual int  Select(unsigned short UnitNo,tagSrvCommLinkMsgQueue * LinkMsg,tagSrvCommDataMsgQueue * DataMsg);
	virtual int  RecvFrame(unsigned long LinkNo,tagFrameHead * OutHead,char * OutBuf,unsigned short InSize);
	virtual int  SendFrame(unsigned long LinkNo,tagFrameHead * InHead,char * InBuf,unsigned short InSize,int SendTimes = 0);
public:
	virtual int  SetLinkAddtionData(unsigned long LinkNo,unsigned long AddtionData);
	virtual int  GetLinkAddtionData(unsigned long LinkNo,unsigned long * AddtionData);
public:
	virtual int  GetLinkUnitInfo(unsigned short UnitNo,tagSrvCommLinkQueue * Out,unsigned short InSize = MSRVCOMM_UNIT_LINK_COUNT);
	virtual int  GetLinkInfo(unsigned long LinkNo,tagSrvCommLinkQueue * Out);
public:
	virtual float GetSendAmount(void);
	virtual float GetRecvAmount(void);
	virtual unsigned long GetSendCommBand(void);
	virtual unsigned long GetRecvCommBand(void);
	virtual unsigned long GetWaitRequestCount(void);
public:
	virtual bool VerifyIP(char * IPAddr);
public:
	static int  SendSocketFrame(SOCKET InSocket,tagFrameHead * InHead,char * InBuf,unsigned short InSize);
	static int  SendSocketBlockFrame(SOCKET InSocket,tagFrameHead * InHead,char * InBuf,unsigned short Offset,unsigned short BlockSize,unsigned short BlockCount);
	static int  RecvSocketFrameTemp(SOCKET InSocket,tagFrameHead * OutHead,char * OutBuf,unsigned short InSize);
	static int  RecvSocketFrame(SOCKET InSocket,tagFrameHead * OutHead,char * OutBuf,unsigned short InSize);
public:
	//获取通讯权值
	static float GetCommSendFluxValue(void);

	DECLARE_LMYUNIT(MSrvCommUnit)
};
//--------------------------------------------------------------------------------------------------------------------------------
#pragma pack()
//--------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------
