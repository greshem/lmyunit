#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommUnit* srvcommunit = new MSrvCommUnit();
    unsigned long AddtionData = 0;
    srvcommunit->GetLinkAddtionData(1, &AddtionData); //target call
    return 0;
}
