#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommLinkQueue* srvcommlinkqueue = new MSrvCommLinkQueue();
    srvcommlinkqueue->SetLinkAddtionData(1, 2, 3); //target call
    return 0;
}
