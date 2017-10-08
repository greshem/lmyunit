#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommSendGroup *srvcommsendgroup = new MSrvCommSendGroup();
    delete(srvcommsendgroup); //target call
    return 0;
}
