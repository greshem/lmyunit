#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommRecvGroup* srvcommrecvgroup = new MSrvCommRecvGroup();
    srvcommrecvgroup->GetWaitRequestCount(); //target call
    return 0;
}
