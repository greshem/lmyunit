#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_SubPrice* subprice = new MFD_SubPrice();
    unsigned long BitOffset [] = {
        0,
        1,
        2,
        3};
    subprice->ReadDataFromBuf(BitOffset); //target call
    return 0;
}
