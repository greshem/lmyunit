#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MLocalComplexSection* localcomplexsection = new MLocalComplexSection();
    localcomplexsection->UnAttch(); //target call
    return 0;
}
