#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_MarketID* marketid = new MFD_MarketID();
    marketid->operator=('A'); //target call
    return 0;
}
