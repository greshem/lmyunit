#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MCharLoopGroupSt* charloopgroupst = new MCharLoopGroupSt();
    char OutBuf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    charloopgroupst->GetData(OutBuf, 4); //target call
    return 0;
}
