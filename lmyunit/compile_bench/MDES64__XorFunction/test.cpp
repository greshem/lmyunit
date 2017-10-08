#include <lmyunit/unitlib.h>

class MDES64_SubClass: public MDES64
{
public:
    MDES64_SubClass():MDES64(){}

    void XorFunction_Wrapper() {
       unsigned char* InBuf = (unsigned char*) malloc(sizeof(unsigned char)*256);
       unsigned char XorBuf [] = {
           'A',
           'B',
           'C',
           'D',
           '\0'};
       this->XorFunction(InBuf, XorBuf, 4);
    }
};//MDES64_SubClass

int main(int argc, char *argv[])
{
    MDES64_SubClass* mdes64 = new MDES64_SubClass();
    mdes64->XorFunction_Wrapper(); //target call
    return 0;
}
