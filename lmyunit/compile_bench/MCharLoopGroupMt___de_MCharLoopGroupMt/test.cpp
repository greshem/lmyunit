#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MCharLoopGroupMt *charloopgroupmt = new MCharLoopGroupMt();
    delete(charloopgroupmt); //target call
    return 0;
}
