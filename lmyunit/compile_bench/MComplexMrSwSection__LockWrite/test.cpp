#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MComplexMrSwSection* complexmrswsection = new MComplexMrSwSection();
    complexmrswsection->LockWrite(1); //target call
    return 0;
}
