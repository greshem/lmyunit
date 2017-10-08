#include <unitcode/msrvcomm.h>

class MLoopGroupMt_tagSrvCommLinkMsg__SubClass: public MLoopGroupMt<tagSrvCommLinkMsg>
{
public:
    MLoopGroupMt_tagSrvCommLinkMsg__SubClass():MLoopGroupMt<tagSrvCommLinkMsg>(){}
};//MLoopGroupMt_tagSrvCommLinkMsg__SubClass

int main(int argc, char *argv[])
{
    MLoopGroupMt_tagSrvCommLinkMsg__SubClass *loopgroupmt = new MLoopGroupMt_tagSrvCommLinkMsg__SubClass();
    delete(loopgroupmt); //target call
    return 0;
}
