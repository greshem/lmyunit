#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_SubPrice *subprice = new MFD_SubPrice();
    delete(subprice); //target call
    return 0;
}
