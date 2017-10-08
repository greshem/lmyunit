#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    tagSystemInfoCpuInfo Out;
    MSystemInfo::GetCPUInfo(&Out, 4); //target call
    return 0;
}
