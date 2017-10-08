#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MComplexMrSwSection* complexmrswsection = new MComplexMrSwSection();
    complexmrswsection->UnLock(); //target call
    return 0;
}
