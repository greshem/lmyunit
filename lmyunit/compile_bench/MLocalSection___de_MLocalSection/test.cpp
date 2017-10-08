#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MLocalSection *localsection = new MLocalSection();
    delete(localsection); //target call
    return 0;
}
