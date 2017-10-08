#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MLoopGroupSt<tagSrvCommLinkMsg> *loopgroupst = new MLoopGroupSt<tagSrvCommLinkMsg>();
    delete(loopgroupst); //target call
    return 0;
}
