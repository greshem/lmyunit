#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommSendGroup* srvcommsendgroup = new MSrvCommSendGroup();
    srvcommsendgroup->CloseLink(1); //target call
    return 0;
}
