#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_SignSubPrice *signsubprice = new MFD_SignSubPrice();
    delete(signsubprice); //target call
    return 0;
}
