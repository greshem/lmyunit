#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MSystemInfo *systeminfo = new MSystemInfo();
    delete(systeminfo); //target call
    return 0;
}
