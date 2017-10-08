#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommUnit* srvcommunit = new MSrvCommUnit();
    srvcommunit->GetRecvAmount(); //target call
    return 0;
}
