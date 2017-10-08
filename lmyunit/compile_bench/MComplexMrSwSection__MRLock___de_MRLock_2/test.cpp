#include <lmyunit/unitlib.h>

class MComplexMrSwSection_MRLock_SubClass: public MComplexMrSwSection::MRLock
{
public:
    MComplexMrSwSection_MRLock_SubClass(MComplexMrSwSection& section, int& nRlt):MComplexMrSwSection::MRLock(section, nRlt){}
};//MComplexMrSwSection_MRLock_SubClass

int main(int argc, char *argv[])
{
    MComplexMrSwSection section;
    int nRlt = 1;
    MComplexMrSwSection_MRLock_SubClass *mrlock = new MComplexMrSwSection_MRLock_SubClass(section, (int&)nRlt);
    delete(mrlock); //target call
    return 0;
}
