#include <lmyunit/unitlib.h>

class MMrSwSection_SubClass: public MMrSwSection
{
public:
    MMrSwSection_SubClass():MMrSwSection(){}
};//MMrSwSection_SubClass

int main(int argc, char *argv[])
{
    MMrSwSection_SubClass* mrswsection = new MMrSwSection_SubClass(); //target call
    return 0;
}
