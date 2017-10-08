#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommUnit* srvcommunit = new MSrvCommUnit();
    tagSrvCommLinkQueue Out;
    srvcommunit->GetLinkUnitInfo(1, &Out, 4); //target call
    return 0;
}
