#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_SubPrice* subprice = new MFD_SubPrice();
    subprice->operator=(1); //target call
    return 0;
}
