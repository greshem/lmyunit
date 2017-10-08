#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_Price* price = new MFD_Price();
    unsigned long BitOffset [] = {
        0,
        1,
        2,
        3};
    price->WriteDataToBuf(BitOffset); //target call
    return 0;
}
