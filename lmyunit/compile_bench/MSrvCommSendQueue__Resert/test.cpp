#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommSendQueue* srvcommsendqueue = new MSrvCommSendQueue();
    srvcommsendqueue->Resert(1, 2, (long) 0); //target call
    return 0;
}
