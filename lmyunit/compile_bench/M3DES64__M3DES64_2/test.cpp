#include <lmyunit/unitlib.h>

class M3DES64_SubClass: public M3DES64
{
public:
    M3DES64_SubClass():M3DES64(){}
};//M3DES64_SubClass

int main(int argc, char *argv[])
{
    M3DES64_SubClass* m3des64 = new M3DES64_SubClass(); //target call
    return 0;
}
