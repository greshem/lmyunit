#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommRecvQueue* srvcommrecvqueue = new MSrvCommRecvQueue();
    MLoopGroupMt<tagSrvCommLinkMsg>* loopgroupmt = new MLoopGroupMt<tagSrvCommLinkMsg>();
    tagSrvCommLinkMsg Msg;
    loopgroupmt->GetData(&Msg);

    srvcommrecvqueue->AddLinkMsg(&Msg); //target call
    return 0;
}
