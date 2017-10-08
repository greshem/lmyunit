#include <lmyunit/unitlib.h>

class MDll_SubClass: public MDll
{
public:
    MDll_SubClass():MDll(){}
};//MDll_SubClass

int main(int argc, char *argv[])
{
    MDll_SubClass* dll = new MDll_SubClass(); //target call
    return 0;
}
