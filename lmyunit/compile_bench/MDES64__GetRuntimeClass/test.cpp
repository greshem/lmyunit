#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MDES64* mdes64 = new MDES64();
    mdes64->GetRuntimeClass(); //target call
    return 0;
}
