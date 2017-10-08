#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MComplexMrSwSection section;
    int nRlt = 1;
    MComplexMrSwSection::MRLock* mrlock = new MComplexMrSwSection::MRLock(section, (int&)nRlt, 2); //target call
    return 0;
}
