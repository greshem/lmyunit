#include <lmyunit/unitlib.h>

class MFD_MarketID_SubClass: public MFD_MarketID
{
public:
    MFD_MarketID_SubClass():MFD_MarketID(){}
};//MFD_MarketID_SubClass

int main(int argc, char *argv[])
{
    MFD_MarketID_SubClass* marketid = new MFD_MarketID_SubClass(); //target call
    return 0;
}
