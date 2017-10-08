#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MCharLoopGroupMt* charloopgroupmt = new MCharLoopGroupMt();
    charloopgroupmt->Instance(4); //target call
    return 0;
}
