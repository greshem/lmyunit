#include <lmyunit/unitlib.h>

class MComplexMrSwSection_MRLock_SubClass: public MComplexMrSwSection::MRLock
{
public:
    MComplexMrSwSection_MRLock_SubClass(MComplexMrSwSection& section, int& nRlt, unsigned long nTO):MComplexMrSwSection::MRLock(section, nRlt, nTO){}
};//MComplexMrSwSection_MRLock_SubClass

int main(int argc, char *argv[])
{
    MComplexMrSwSection section;
    int nRlt = 1;
    MComplexMrSwSection_MRLock_SubClass* mrlock = new MComplexMrSwSection_MRLock_SubClass(section, (int&)nRlt, 2); //target call
    return 0;
}
