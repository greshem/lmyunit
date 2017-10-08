#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_MarketID *marketid = new MFD_MarketID();
    delete(marketid); //target call
    return 0;
}
