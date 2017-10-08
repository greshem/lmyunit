#include <lmyunit/unitlib.h>

class MComplexMrSwSection_SubClass: public MComplexMrSwSection
{
public:
    MComplexMrSwSection_SubClass():MComplexMrSwSection(){}
};//MComplexMrSwSection_SubClass

int main(int argc, char *argv[])
{
    MComplexMrSwSection_SubClass* complexmrswsection = new MComplexMrSwSection_SubClass(); //target call
    return 0;
}
