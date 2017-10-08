#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommSendQueue* srvcommsendqueue = new MSrvCommSendQueue();
    MSrvCommSubUnit* Parent = new MSrvCommSubUnit();
    srvcommsendqueue->Instance(Parent); //target call
    return 0;
}
