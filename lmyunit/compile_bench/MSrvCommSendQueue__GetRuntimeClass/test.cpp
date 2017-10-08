#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommSendQueue* srvcommsendqueue = new MSrvCommSendQueue();
    srvcommsendqueue->GetRuntimeClass(); //target call
    return 0;
}
