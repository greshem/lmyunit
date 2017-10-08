#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommSendGroup* srvcommsendgroup = new MSrvCommSendGroup();
    MSrvCommSendQueue* Parent = new MSrvCommSendQueue();
    srvcommsendgroup->Instance(Parent); //target call
    return 0;
}
