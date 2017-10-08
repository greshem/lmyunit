#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommLinkQueue* srvcommlinkqueue = new MSrvCommLinkQueue();
    unsigned long AddtionData = 0;
    srvcommlinkqueue->GetLinkAddtionData(1, 2, &AddtionData); //target call
    return 0;
}
