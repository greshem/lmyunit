#include <lmyunit/unitlib.h>

class MDES64_SubClass: public MDES64
{
public:
    MDES64_SubClass():MDES64(){}

    void FFunction_Wrapper() {
       unsigned char* InBuf = (unsigned char*) malloc(sizeof(unsigned char)*256);
       unsigned char* KeyBuf = (unsigned char*) malloc(sizeof(unsigned char)*256);
       this->FFunction(InBuf, KeyBuf);
    }
};//MDES64_SubClass

int main(int argc, char *argv[])
{
    MDES64_SubClass* mdes64 = new MDES64_SubClass();
    mdes64->FFunction_Wrapper(); //target call
    return 0;
}
