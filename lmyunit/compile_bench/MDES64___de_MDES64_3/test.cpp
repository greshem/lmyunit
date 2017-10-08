#include <lmyunit/unitlib.h>

class MDES64_SubClass: public MDES64
{
public:
    MDES64_SubClass():MDES64(){}
};//MDES64_SubClass

int main(int argc, char *argv[])
{
    MDES64_SubClass *mdes64 = new MDES64_SubClass();
    delete(mdes64); //target call
    return 0;
}
