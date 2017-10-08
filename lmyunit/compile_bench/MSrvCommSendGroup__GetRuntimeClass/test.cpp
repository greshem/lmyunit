#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommSendGroup* srvcommsendgroup = new MSrvCommSendGroup();
    srvcommsendgroup->GetRuntimeClass(); //target call
    return 0;
}
