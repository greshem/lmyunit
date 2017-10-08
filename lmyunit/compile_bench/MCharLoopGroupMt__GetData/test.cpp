#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MCharLoopGroupMt* charloopgroupmt = new MCharLoopGroupMt();
    char OutBuf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    charloopgroupmt->GetData(OutBuf, 4); //target call
    return 0;
}
