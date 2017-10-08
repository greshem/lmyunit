#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    tagSystemInfoBIOSInfo Out;
    MSystemInfo::GetBIOSInfo(&Out); //target call
    return 0;
}
