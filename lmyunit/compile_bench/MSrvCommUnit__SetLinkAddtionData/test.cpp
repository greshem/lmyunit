#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommUnit* srvcommunit = new MSrvCommUnit();
    srvcommunit->SetLinkAddtionData(1, 2); //target call
    return 0;
}
