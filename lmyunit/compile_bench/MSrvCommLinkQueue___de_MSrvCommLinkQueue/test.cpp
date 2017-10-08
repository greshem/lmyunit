#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommLinkQueue *srvcommlinkqueue = new MSrvCommLinkQueue();
    delete(srvcommlinkqueue); //target call
    return 0;
}
