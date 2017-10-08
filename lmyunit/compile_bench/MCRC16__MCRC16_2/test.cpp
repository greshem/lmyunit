#include <lmyunit/unitlib.h>

class MCRC16_SubClass: public MCRC16
{
public:
    MCRC16_SubClass():MCRC16(){}
};//MCRC16_SubClass

int main(int argc, char *argv[])
{
    MCRC16_SubClass* mcrc16 = new MCRC16_SubClass(); //target call
    return 0;
}
