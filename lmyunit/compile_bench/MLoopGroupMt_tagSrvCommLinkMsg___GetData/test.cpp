#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MLoopGroupMt<tagSrvCommLinkMsg>* loopgroupmt = new MLoopGroupMt<tagSrvCommLinkMsg>();
    tagSrvCommLinkMsg Out;
    loopgroupmt->GetData(&Out); //target call
    return 0;
}
