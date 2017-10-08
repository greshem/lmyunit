#include <unitcode/msrvcomm.h>

class MSrvCommLinkQueue_SubClass: public MSrvCommLinkQueue
{
public:
    MSrvCommLinkQueue_SubClass():MSrvCommLinkQueue(){}
};//MSrvCommLinkQueue_SubClass

int main(int argc, char *argv[])
{
    MSrvCommLinkQueue_SubClass *srvcommlinkqueue = new MSrvCommLinkQueue_SubClass();
    delete(srvcommlinkqueue); //target call
    return 0;
}
