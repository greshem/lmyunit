#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MMrSwSection section;
    int nRlt = 1;
    MMrSwSection::MRLock* mrlock = new MMrSwSection::MRLock(section, (int&)nRlt, 2); //target call
    return 0;
}
