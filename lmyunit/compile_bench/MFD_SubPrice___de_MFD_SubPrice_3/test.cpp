#include <lmyunit/unitlib.h>

class MFD_SubPrice_SubClass: public MFD_SubPrice
{
public:
    MFD_SubPrice_SubClass():MFD_SubPrice(){}
};//MFD_SubPrice_SubClass

int main(int argc, char *argv[])
{
    MFD_SubPrice_SubClass *subprice = new MFD_SubPrice_SubClass();
    delete(subprice); //target call
    return 0;
}
