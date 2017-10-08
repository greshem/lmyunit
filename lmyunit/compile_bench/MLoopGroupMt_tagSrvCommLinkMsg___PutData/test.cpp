#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MLoopGroupMt<tagSrvCommLinkMsg>* loopgroupmt = new MLoopGroupMt<tagSrvCommLinkMsg>();
    tagSrvCommLinkMsg In;
    loopgroupmt->GetData(&In);

    loopgroupmt->PutData(&In); //target call
    return 0;
}
