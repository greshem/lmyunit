#include <lmyunit/unitlib.h>

class MLocalSection_SubClass: public MLocalSection
{
public:
    MLocalSection_SubClass():MLocalSection(){}
};//MLocalSection_SubClass

int main(int argc, char *argv[])
{
    MLocalSection_SubClass *localsection = new MLocalSection_SubClass();
    delete(localsection); //target call
    return 0;
}
