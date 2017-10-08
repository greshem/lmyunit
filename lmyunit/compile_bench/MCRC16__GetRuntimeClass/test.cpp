#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MCRC16* mcrc16 = new MCRC16();
    mcrc16->GetRuntimeClass(); //target call
    return 0;
}
