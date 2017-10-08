#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MLocalComplexSection* localcomplexsection = new MLocalComplexSection();
    MComplexMrSwSection* section = new MComplexMrSwSection();
    localcomplexsection->AttchLockWrite(section, 1); //target call
    return 0;
}
