#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    tagHardWareInfo Out;
    MSystemInfo::GetSystemHardWareInfo(&Out); //target call
    return 0;
}
