#include <lmyunit/unitlib.h>

class MMrSwSection_MWLock_SubClass: public MMrSwSection::MWLock
{
public:
    MMrSwSection_MWLock_SubClass(MMrSwSection& section, int& nRlt, unsigned short nTry):MMrSwSection::MWLock(section, nRlt, nTry){}
};//MMrSwSection_MWLock_SubClass

int main(int argc, char *argv[])
{
    MMrSwSection section;
    int nRlt = 1;
    MMrSwSection_MWLock_SubClass* mwlock = new MMrSwSection_MWLock_SubClass(section, (int&)nRlt, 2); //target call
    return 0;
}
