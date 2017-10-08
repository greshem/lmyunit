#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MCharLoopGroupSt *charloopgroupst = new MCharLoopGroupSt();
    delete(charloopgroupst); //target call
    return 0;
}
