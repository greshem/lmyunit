#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MComplexMrSwSection* complexmrswsection = new MComplexMrSwSection();
    complexmrswsection->GetRuntimeClass(); //target call
    return 0;
}
