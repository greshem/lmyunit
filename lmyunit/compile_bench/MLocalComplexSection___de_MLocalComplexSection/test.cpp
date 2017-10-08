#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MLocalComplexSection *localcomplexsection = new MLocalComplexSection();
    delete(localcomplexsection); //target call
    return 0;
}
