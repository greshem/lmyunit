#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommSendGroup* srvcommsendgroup = new MSrvCommSendGroup();
    srvcommsendgroup->Resert(1, (long) 0); //target call
    return 0;
}
