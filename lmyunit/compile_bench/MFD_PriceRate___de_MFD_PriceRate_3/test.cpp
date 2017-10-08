#include <lmyunit/unitlib.h>

class MFD_PriceRate_SubClass: public MFD_PriceRate
{
public:
    MFD_PriceRate_SubClass():MFD_PriceRate(){}
};//MFD_PriceRate_SubClass

int main(int argc, char *argv[])
{
    MFD_PriceRate_SubClass *pricerate = new MFD_PriceRate_SubClass();
    delete(pricerate); //target call
    return 0;
}
