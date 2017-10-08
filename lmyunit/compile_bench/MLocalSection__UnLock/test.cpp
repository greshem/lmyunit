#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MLocalSection* localsection = new MLocalSection();
    localsection->UnLock(); //target call
    return 0;
}
