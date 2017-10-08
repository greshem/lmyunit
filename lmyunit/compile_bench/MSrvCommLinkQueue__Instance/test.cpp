#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommLinkQueue* srvcommlinkqueue = new MSrvCommLinkQueue();
    MSrvCommSubUnit* Parent = new MSrvCommSubUnit();
    srvcommlinkqueue->Instance(Parent, 1); //target call
    return 0;
}
