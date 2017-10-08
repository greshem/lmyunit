#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommLinkQueue* srvcommlinkqueue = new MSrvCommLinkQueue();
    srvcommlinkqueue->UpdateRecvInfo(1, 2, 3); //target call
    return 0;
}
