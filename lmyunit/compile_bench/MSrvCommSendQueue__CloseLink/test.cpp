#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommSendQueue* srvcommsendqueue = new MSrvCommSendQueue();
    srvcommsendqueue->CloseLink(1); //target call
    return 0;
}
