#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MCriticalSection section;
    MCriticalSection::MLock* lock = new MCriticalSection::MLock(section); //target call
    return 0;
}
