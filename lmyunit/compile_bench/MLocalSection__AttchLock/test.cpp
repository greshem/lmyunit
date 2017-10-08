#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MLocalSection* localsection = new MLocalSection();
    MCriticalSection* In = new MCriticalSection();
    localsection->AttchLock(In); //target call
    return 0;
}
