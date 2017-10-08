#include <lmyunit/unitlib.h>

class MMrSwSection_MRLock_SubClass: public MMrSwSection::MRLock
{
public:
    MMrSwSection_MRLock_SubClass(MMrSwSection& section, int& nRlt):MMrSwSection::MRLock(section, nRlt){}
};//MMrSwSection_MRLock_SubClass

int main(int argc, char *argv[])
{
    MMrSwSection section;
    int nRlt = 1;
    MMrSwSection_MRLock_SubClass *mrlock = new MMrSwSection_MRLock_SubClass(section, (int&)nRlt);
    delete(mrlock); //target call
    return 0;
}
