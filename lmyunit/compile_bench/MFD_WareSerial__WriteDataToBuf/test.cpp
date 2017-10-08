#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_WareSerial* wareserial = new MFD_WareSerial();
    unsigned long BitOffset [] = {
        0,
        1,
        2,
        3};
    wareserial->WriteDataToBuf(BitOffset); //target call
    return 0;
}
