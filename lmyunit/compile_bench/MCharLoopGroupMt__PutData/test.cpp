#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MCharLoopGroupMt* charloopgroupmt = new MCharLoopGroupMt();
    char InBuf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    charloopgroupmt->PutData(InBuf, 4); //target call
    return 0;
}
