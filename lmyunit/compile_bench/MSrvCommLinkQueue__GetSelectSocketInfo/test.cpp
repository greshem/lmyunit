#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommLinkQueue* srvcommlinkqueue = new MSrvCommLinkQueue();
    tagSrvCommSelectLinkInfo Out;
    srvcommlinkqueue->GetSelectSocketInfo(&Out, 4); //target call
    return 0;
}
