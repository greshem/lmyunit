#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MCharLoopGroupMt* charloopgroupmt = new MCharLoopGroupMt();
    charloopgroupmt->Release(); //target call
    return 0;
}
