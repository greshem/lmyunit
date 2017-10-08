#include <lmyunit/unitlib.h>

class MCharLoopGroupMt_SubClass: public MCharLoopGroupMt
{
public:
    MCharLoopGroupMt_SubClass():MCharLoopGroupMt(){}
};//MCharLoopGroupMt_SubClass

int main(int argc, char *argv[])
{
    MCharLoopGroupMt_SubClass *charloopgroupmt = new MCharLoopGroupMt_SubClass();
    delete(charloopgroupmt); //target call
    return 0;
}
