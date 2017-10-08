#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MLoopGroupSt<tagSrvCommLinkMsg>* loopgroupst = new MLoopGroupSt<tagSrvCommLinkMsg>();
    tagSrvCommLinkMsg Out;
    loopgroupst->GetData(&Out); //target call
    return 0;
}
