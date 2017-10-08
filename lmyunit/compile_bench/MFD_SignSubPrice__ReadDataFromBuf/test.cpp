#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_SignSubPrice* signsubprice = new MFD_SignSubPrice();
    unsigned long BitOffset [] = {
        0,
        1,
        2,
        3};
    signsubprice->ReadDataFromBuf(BitOffset); //target call
    return 0;
}
