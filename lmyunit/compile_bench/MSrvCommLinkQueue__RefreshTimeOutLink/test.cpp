#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommLinkQueue* srvcommlinkqueue = new MSrvCommLinkQueue();
    srvcommlinkqueue->RefreshTimeOutLink(); //target call
    return 0;
}
