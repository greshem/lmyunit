#include <lmyunit/unitlib.h>

class MFD_Price_SubClass: public MFD_Price
{
public:
    MFD_Price_SubClass():MFD_Price(){}
};//MFD_Price_SubClass

int main(int argc, char *argv[])
{
    MFD_Price_SubClass *price = new MFD_Price_SubClass();
    delete(price); //target call
    return 0;
}
