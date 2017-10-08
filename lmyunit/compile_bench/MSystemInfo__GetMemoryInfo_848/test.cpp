#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    tagSystemInfoMemoryInfo Out;
    MSystemInfo::GetMemoryInfo(&Out); //target call
    return 0;
}
