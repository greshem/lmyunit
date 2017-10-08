#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MComplexMrSwSection section;
    int nRlt = 1;
    MComplexMrSwSection::MWLock* mwlock = new MComplexMrSwSection::MWLock(section, (int&)nRlt, 2); //target call
    return 0;
}
