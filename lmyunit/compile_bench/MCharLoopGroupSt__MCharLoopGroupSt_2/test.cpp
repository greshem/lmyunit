#include <lmyunit/unitlib.h>

class MCharLoopGroupSt_SubClass: public MCharLoopGroupSt
{
public:
    MCharLoopGroupSt_SubClass():MCharLoopGroupSt(){}
};//MCharLoopGroupSt_SubClass

int main(int argc, char *argv[])
{
    MCharLoopGroupSt_SubClass* charloopgroupst = new MCharLoopGroupSt_SubClass(); //target call
    return 0;
}
