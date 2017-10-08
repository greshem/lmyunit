#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MCriticalSection* criticalsection = new MCriticalSection();
    criticalsection->GetRuntimeClass(); //target call
    return 0;
}
