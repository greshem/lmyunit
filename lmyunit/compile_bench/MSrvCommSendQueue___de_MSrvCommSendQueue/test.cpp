#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommSendQueue *srvcommsendqueue = new MSrvCommSendQueue();
    delete(srvcommsendqueue); //target call
    return 0;
}
