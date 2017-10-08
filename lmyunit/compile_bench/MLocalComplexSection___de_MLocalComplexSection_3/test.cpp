#include <lmyunit/unitlib.h>

class MLocalComplexSection_SubClass: public MLocalComplexSection
{
public:
    MLocalComplexSection_SubClass():MLocalComplexSection(){}
};//MLocalComplexSection_SubClass

int main(int argc, char *argv[])
{
    MLocalComplexSection_SubClass *localcomplexsection = new MLocalComplexSection_SubClass();
    delete(localcomplexsection); //target call
    return 0;
}
