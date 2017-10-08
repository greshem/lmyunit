#include <lmyunit/unitlib.h>

class MDES64_SubClass: public MDES64
{
public:
    MDES64_SubClass():MDES64(){}

    void RotateL_Wrapper() {
       unsigned char InBuf [] = {
           'A',
           'B',
           'C',
           'D',
           '\0'};
       this->RotateL(InBuf, 4, 'E');
    }
};//MDES64_SubClass

int main(int argc, char *argv[])
{
    MDES64_SubClass* mdes64 = new MDES64_SubClass();
    mdes64->RotateL_Wrapper(); //target call
    return 0;
}
