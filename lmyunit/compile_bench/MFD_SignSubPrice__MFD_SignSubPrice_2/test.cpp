#include <lmyunit/unitlib.h>

class MFD_SignSubPrice_SubClass: public MFD_SignSubPrice
{
public:
    MFD_SignSubPrice_SubClass():MFD_SignSubPrice(){}
};//MFD_SignSubPrice_SubClass

int main(int argc, char *argv[])
{
    MFD_SignSubPrice_SubClass* signsubprice = new MFD_SignSubPrice_SubClass(); //target call
    return 0;
}
