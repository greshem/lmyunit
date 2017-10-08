#include <lmyunit/unitlib.h>

class MComplexMrSwSection_MWLock_SubClass: public MComplexMrSwSection::MWLock
{
public:
    MComplexMrSwSection_MWLock_SubClass(MComplexMrSwSection& section, int& nRlt, unsigned long nTO):MComplexMrSwSection::MWLock(section, nRlt, nTO){}
};//MComplexMrSwSection_MWLock_SubClass

int main(int argc, char *argv[])
{
    MComplexMrSwSection section;
    int nRlt = 1;
    MComplexMrSwSection_MWLock_SubClass* mwlock = new MComplexMrSwSection_MWLock_SubClass(section, (int&)nRlt, 2); //target call
    return 0;
}
