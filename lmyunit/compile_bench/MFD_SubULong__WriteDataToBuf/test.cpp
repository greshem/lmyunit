#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_SubULong* subulong = new MFD_SubULong();
    unsigned long BitOffset [] = {
        0,
        1,
        2,
        3};
    subulong->WriteDataToBuf(BitOffset); //target call
    return 0;
}
