#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommUnit* srvcommunit = new MSrvCommUnit();
    tagSrvCommLinkQueue Out;
    srvcommunit->GetLinkInfo(1, &Out); //target call
    return 0;
}
