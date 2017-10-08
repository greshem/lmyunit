#include <lmyunit/unitlib.h>

class MDES64_SubClass: public MDES64
{
public:
    MDES64_SubClass():MDES64(){}

    void SFunction_Wrapper() {
       unsigned char* InBuf = (unsigned char*) malloc(sizeof(unsigned char)*256);
       unsigned char* OutBuf = (unsigned char*) malloc(sizeof(unsigned char)*256);
       this->SFunction(InBuf, OutBuf);
    }
};//MDES64_SubClass

int main(int argc, char *argv[])
{
    MDES64_SubClass* mdes64 = new MDES64_SubClass();
    mdes64->SFunction_Wrapper(); //target call
    return 0;
}
