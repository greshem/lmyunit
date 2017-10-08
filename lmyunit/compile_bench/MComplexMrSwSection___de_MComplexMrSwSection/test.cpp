#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MComplexMrSwSection *complexmrswsection = new MComplexMrSwSection();
    delete(complexmrswsection); //target call
    return 0;
}
