#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_PriceRate *pricerate = new MFD_PriceRate();
    delete(pricerate); //target call
    return 0;
}
