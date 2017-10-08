#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MCharLoopGroupSt* charloopgroupst = new MCharLoopGroupSt();
    char InBuf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    charloopgroupst->PutData(InBuf, 4); //target call
    return 0;
}
