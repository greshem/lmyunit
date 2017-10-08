#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MCriticalSection *criticalsection = new MCriticalSection();
    delete(criticalsection); //target call
    return 0;
}
