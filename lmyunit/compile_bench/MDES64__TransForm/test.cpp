#include <lmyunit/unitlib.h>

class MDES64_SubClass: public MDES64
{
public:
    MDES64_SubClass():MDES64(){}

    void TransForm_Wrapper() {
       unsigned char InBuf [] = {
           'A',
           'B',
           'C',
           'D',
           '\0'};
       unsigned char* OutBuf = (unsigned char*) malloc(sizeof(unsigned char)*256);
       unsigned char Table [] = {
           'E',
           'F',
           'G',
           'H',
           '\0'};
       this->TransForm(
          InBuf,
          4,
          OutBuf,
          Table);
    }
};//MDES64_SubClass

int main(int argc, char *argv[])
{
    MDES64_SubClass* mdes64 = new MDES64_SubClass();
    mdes64->TransForm_Wrapper(); //target call
    return 0;
}
