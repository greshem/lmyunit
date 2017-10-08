#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommSendQueue* srvcommsendqueue = new MSrvCommSendQueue();
    tagSrvCommSelectLinkInfo Out;
    srvcommsendqueue->GetSelectSocketInfo(&Out, 4); //target call
    return 0;
}
