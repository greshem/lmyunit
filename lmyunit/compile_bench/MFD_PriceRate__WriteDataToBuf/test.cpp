#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_PriceRate* pricerate = new MFD_PriceRate();
    unsigned long BitOffset [] = {
        0,
        1,
        2,
        3};
    pricerate->WriteDataToBuf(BitOffset); //target call
    return 0;
}
