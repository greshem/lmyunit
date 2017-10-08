#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommLinkQueue* srvcommlinkqueue = new MSrvCommLinkQueue();
    tagSrvCommLinkQueue Out;
    srvcommlinkqueue->GetLinkInfo(1, 2, &Out); //target call
    return 0;
}
