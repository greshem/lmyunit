#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MCharLoopGroupSt* charloopgroupst = new MCharLoopGroupSt();
    charloopgroupst->GetRuntimeClass(); //target call
    return 0;
}
