#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommSendGroup* srvcommsendgroup = new MSrvCommSendGroup();
    unsigned long* LinkNo = (unsigned long*) malloc(sizeof(unsigned long)*256);
    long* SocketId = (long*) malloc(sizeof(long)*256);
    srvcommsendgroup->IsEmpty(LinkNo, SocketId); //target call
    return 0;
}
