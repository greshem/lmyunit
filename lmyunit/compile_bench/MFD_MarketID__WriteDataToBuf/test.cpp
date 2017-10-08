#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_MarketID* marketid = new MFD_MarketID();
    unsigned long BitOffset [] = {
        0,
        1,
        2,
        3};
    marketid->WriteDataToBuf(BitOffset); //target call
    return 0;
}
