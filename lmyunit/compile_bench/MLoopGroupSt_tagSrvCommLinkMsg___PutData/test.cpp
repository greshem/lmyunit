#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MLoopGroupSt<tagSrvCommLinkMsg>* loopgroupst = new MLoopGroupSt<tagSrvCommLinkMsg>();
    MLoopGroupMt<tagSrvCommLinkMsg>* loopgroupmt = new MLoopGroupMt<tagSrvCommLinkMsg>();
    tagSrvCommLinkMsg In;
    loopgroupmt->GetData(&In);

    loopgroupst->PutData(&In); //target call
    return 0;
}
