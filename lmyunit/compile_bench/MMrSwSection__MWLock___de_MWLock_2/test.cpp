#include <lmyunit/unitlib.h>

class MMrSwSection_MWLock_SubClass: public MMrSwSection::MWLock
{
public:
    MMrSwSection_MWLock_SubClass(MMrSwSection& section, int& nRlt):MMrSwSection::MWLock(section, nRlt){}
};//MMrSwSection_MWLock_SubClass

int main(int argc, char *argv[])
{
    MMrSwSection section;
    int nRlt = 1;
    MMrSwSection_MWLock_SubClass *mwlock = new MMrSwSection_MWLock_SubClass(section, (int&)nRlt);
    delete(mwlock); //target call
    return 0;
}
