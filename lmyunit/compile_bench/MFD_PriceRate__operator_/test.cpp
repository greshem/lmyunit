#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_PriceRate* pricerate = new MFD_PriceRate();
    pricerate->operator=(1); //target call
    return 0;
}
