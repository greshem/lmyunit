#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MLoopGroupSt<tagSrvCommLinkMsg>* loopgroupst = new MLoopGroupSt<tagSrvCommLinkMsg>();
    loopgroupst->Instance(4); //target call
    return 0;
}
