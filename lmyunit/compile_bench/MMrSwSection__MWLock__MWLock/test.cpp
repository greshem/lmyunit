#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MMrSwSection section;
    int nRlt = 1;
    MMrSwSection::MWLock* mwlock = new MMrSwSection::MWLock(section, (int&)nRlt, 2); //target call
    return 0;
}
