#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MLoopGroupMt<tagSrvCommLinkMsg>* loopgroupmt = new MLoopGroupMt<tagSrvCommLinkMsg>();
    loopgroupmt->Instance(4); //target call
    return 0;
}
