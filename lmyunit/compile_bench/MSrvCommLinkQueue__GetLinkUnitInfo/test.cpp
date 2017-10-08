#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommLinkQueue* srvcommlinkqueue = new MSrvCommLinkQueue();
    tagSrvCommLinkQueue Out;
    srvcommlinkqueue->GetLinkUnitInfo(&Out, 4); //target call
    return 0;
}
