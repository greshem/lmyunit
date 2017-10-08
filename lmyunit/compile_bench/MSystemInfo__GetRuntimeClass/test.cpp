#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MSystemInfo* systeminfo = new MSystemInfo();
    systeminfo->GetRuntimeClass(); //target call
    return 0;
}
