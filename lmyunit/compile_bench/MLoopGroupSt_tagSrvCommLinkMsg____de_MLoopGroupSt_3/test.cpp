#include <unitcode/msrvcomm.h>

class MLoopGroupSt_tagSrvCommLinkMsg__SubClass: public MLoopGroupSt<tagSrvCommLinkMsg>
{
public:
    MLoopGroupSt_tagSrvCommLinkMsg__SubClass():MLoopGroupSt<tagSrvCommLinkMsg>(){}
};//MLoopGroupSt_tagSrvCommLinkMsg__SubClass

int main(int argc, char *argv[])
{
    MLoopGroupSt_tagSrvCommLinkMsg__SubClass *loopgroupst = new MLoopGroupSt_tagSrvCommLinkMsg__SubClass();
    delete(loopgroupst); //target call
    return 0;
}
