#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    M3DES64* m3des64 = new M3DES64();
    m3des64->GetRuntimeClass(); //target call
    return 0;
}
