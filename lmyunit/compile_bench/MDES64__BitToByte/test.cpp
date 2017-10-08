#include <lmyunit/unitlib.h>

class MDES64_SubClass: public MDES64
{
public:
    MDES64_SubClass():MDES64(){}

    void BitToByte_Wrapper() {
       unsigned char InBuf [] = {
           'A',
           'B',
           'C',
           'D',
           '\0'};
       char* OutBuf = (char*) malloc(sizeof(char)*256);
       this->BitToByte(InBuf, 4, OutBuf);
    }
};//MDES64_SubClass

int main(int argc, char *argv[])
{
    MDES64_SubClass* mdes64 = new MDES64_SubClass();
    mdes64->BitToByte_Wrapper(); //target call
    return 0;
}
