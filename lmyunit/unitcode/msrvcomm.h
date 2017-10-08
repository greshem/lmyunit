//--------------------------------------------------------------------------------------------------------------------------------
//                  ;;;,
//        ,;;;;;: ,;;;:.,;..
//         :;;"`,;;;;;;"":;;					��Ԫ���ƣ���������ͨѶ����
//      ..;;:  .;;,.;;:',;;"
//    ,;;;;;;" :;`',;",;;"						��д���ڣ�2004��5��20
//   :" ,;:` , `:.;;;;;'
//    ,;;;,;:;;,;;;, ,;							��д��Ա��richtech
//   :;;;"` `:;;;;;,;,.;.
//   '""   .;;`.;";:;;;;` ;,					��ע��Ϣ��
//       .;"`  ::. '   .,;;;
//      ""     ';;;;;;;;;;`
//--------------------------------------------------------------------------------------------------------------------------------
#ifndef __LmyUnitMSrvCommH__
#define __LmyUnitMSrvCommH__
//--------------------------------------------------------------------------------------------------------------------------------
//����ͷ�ļ�
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
//Windows����ϵͳ
//................................................................................................................................
#else
//................................................................................................................................
//Linux����ϵͳ
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
#define MAX_FRAME_SIZE				4096					//ÿ����Ϣ����󳤶ȣ�����Ϣͷ����
#define MAX_DATAFRAME_SIZE			(MAX_FRAME_SIZE - sizeof(tagFrameHead))
#define MAX_COMMDATAFRAME_SIZE		4000
#define INVALID_LINK_NO				0xFFFFFFFF				//��Ч����
#define BROADCAST_LINK_NO			0xFFFFFFFE				//�㲥����
//................................................................................................................................
#define MSRVCOMM_UNIT_LINK_COUNT	64						//���ӵ�Ԫ�е���������
#define MSRVCOMM_MAX_ACCEPT_COUNT	64						//������Ķ˿�����
#define MSRVCOMM_TIMEOUT			60000					//��ʱʱ��
#define MSRVCOMM_LINK_RECVSIZE		4150					//ÿ�����ӵĽ��ջ����С
#define MSRVCOMM_LINK_RECVCOUNT		20						//�������������������
#define MSRVCOMM_LINK_SENDSIZE		122880					//ÿ�����ӵķ��ͻ����С
#define MSRVCOMM_SEND_TIMES			3						//�������ݰ�����[ÿһ����Ϣ100����]
//................................................................................................................................
#define	MSRVCOMMUNIT_COMMBAND_TIME	10000					//����ͳ��ʱ�䣨��������ٺ����ڵĴ���ͳ�ƣ�
//................................................................................................................................
#define		MSRVCOMM_LINKORDER(linkno)			((unsigned short)(((linkno) & 0x0000FFFF) / 1000))
#define		MSRVCOMM_LINKUNITNO(linkno)			((unsigned short)(((linkno) & 0xFFFF0000) >> 16 ))
//--------------------------------------------------------------------------------------------------------------------------------
//������Ϣ���� = ������Ϣͷ�� + ������Ϣ����
typedef struct
{
	char	                        Market;					//ͬ����ǣ�Ϊ'$'
    unsigned char	                MainType;				//֡����
	unsigned char	                ChildType;				//������
    unsigned short                  FrameCount;				//�������ݰ�����
    unsigned short                  FrameNo;				//�������ݰ���ţ���0��ʼ��ţ�
    unsigned short                  DataSize;				//���ݳ��ȣ����������ݰ�ͷ����
    unsigned char                   DataStatus;				//����״̬������ѹ�������ܣ�
    unsigned short                  ErrorCode;				//���ݰ�������
    unsigned short                  CheckCode;				//���ݰ�ͷ��У����
    unsigned short                  RequestCode;			//������
	unsigned char					DCDStatus;				//DCD״̬(��2.XЭ����Ч)
															//0 ����
															//1 ��ʼ��
															//2 ����
															//3 �̺�
	unsigned short					DCDTime;				//DCDʱ��(HH * 60 + MM��ʽ)
	unsigned char                   Reserved[1];			//�����ֽ�(��LinBoxϵͳ��,����ֽڱ�ʾ��ǰ�Ϻ��г���ʱ���)
} tagFrameHead;
//................................................................................................................................
typedef struct
{
	unsigned long					LinkNo;					//���Ӻ�
	unsigned long					ParentNo;				//�����Ӻ�
	SOCKET							SocketId;				//��ص�SOCKET
	char							IPAddr[16];				//IP��ַ
	unsigned long					Port;					//�ͻ��˶˿ں�
	unsigned long					LinkType;				//��������
	MCounter						LinkTime;				//����ʱ��
	unsigned long					RecvSize;				//�����ֽ�
	MCounter						RecvTime;				//���һ�ν���ʱ��
	unsigned long					SendSize;				//�����ֽ�
	MCounter						SendTime;				//����ʱ��
	unsigned long					OrderRecord;			//����˳���¼
	unsigned long					AddtionData;			//��������[������Ϊ��������]
	unsigned short					SrvPort;				//����˿ں�
	char							Reserved[8];			//����
} tagSrvCommLinkQueue;
//................................................................................................................................
enum														//��������
{
	MSRVCOMM_LINKTYPE_ACCEPT = 0,							//�ͻ����������ӷ�������������Accept������
	MSRVCOMM_LINKTYPE_NOCONNECT = 128,						//�������������ӿͻ��ˣ���û�е���Connect������
	MSRVCOMM_LINKTYPE_CONNECT,								//�������������ӿͻ��ˣ�����Connect�����ӣ�����֪�����Ƿ�ɹ�
	MSRVCOMM_LINKTYPE_LINKSUC,								//�������������ӿͻ��ˣ�����Connect�����ӣ������ӳɹ�
};
//................................................................................................................................
enum														//�ر�����
{
	MSRVCOMM_CLOSETYPE_SRV = 0,								//�����������ر�
	MSRVCOMM_CLOSETYPE_CLIENT,								//�ͻ��������ر�
	MSRVCOMM_CLOSETYPE_RECV,								//�������ݰ�����
	MSRVCOMM_CLOSETYPE_SEND,								//�������ݰ�����
	MSRVCOMM_CLOSETYPE_TIMEOUT,								//��ʱ�ر�
};
//................................................................................................................................
typedef struct
{
	unsigned short					Serial;					//���
	unsigned long					LinkNo;					//���Ӻ�
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
	MSRVCOMM_LINKMSG_ADD = 0,		//�������
	MSRVCOMM_LINKMSG_CLOSE,			//�ر�����
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
#define		ERROR_MSRVCOMMLINKQUEUE_INVALIDLINK		(ERROR_USER(140))		//ִ��ͨѶ��Ԫ������������[��Ч�����Ӻ�]
#define		ERROR_MSRVCOMMLINKQUEUE_NODATA			(ERROR_USER(141))		//ִ��ͨѶ��Ԫ������������[û��ƥ�������]
#define		ERROR_MSRVCOMMLINKQUEUE_FRAMEHEAD		(ERROR_USER(142))		//ͨѶ��Ԫ�������ݰ���������[���ݰ�ͷ������]
#define		ERROR_MSRVCOMMLINKQUEUE_SENDFULL		(ERROR_USER(143))		//ͨѶ��Ԫ�������ݰ���������[����������]
#define		ERROR_MSRVCOMMLINKQUEUE_NOMEMORY		(ERROR_USER(144))		//ͨѶ��Ԫ��ʼ����������[û���㹻���ڴ���Է���]
#define		ERROR_MSRVCOMMLINKQUEUE_SRVPORT			(ERROR_USER(145))		//ͨѶ��Ԫ��������˿ڷ�������[����������]
#define		ERROR_MSRVCOMMLINKQUEUE_SENDTIMEOUT		(ERROR_USER(146))		//����SOCKET���ݳ�ʱ
#define		ERROR_MSRVCOMMLINKQUEUE_RECVTIMEOUT		(ERROR_USER(147))		//����SOCKET���ݳ�ʱ
#define		ERROR_MSRVCOMMLINKQUEUE_PARAMERROR		(ERROR_USER(148))		//����SOCKET���ݲ�������
#define		ERROR_MSRVCOMMLINKQUEUE_CHECKCODE		(ERROR_USER(149))		//����SOCKET����У�����
#define		ERROR_MSRVCOMMLINKQUEUE_PARAM			(ERROR_USER(150))		//���ͻ����SOCKET���ݲ�������
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
	//��ȡͨѶȨֵ
	static float GetCommSendFluxValue(void);

	DECLARE_LMYUNIT(MSrvCommUnit)
};
//--------------------------------------------------------------------------------------------------------------------------------
#pragma pack()
//--------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------
