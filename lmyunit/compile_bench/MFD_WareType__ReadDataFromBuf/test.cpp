#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_WareType* waretype = new MFD_WareType();
    unsigned long BitOffset [] = {
        0,
        1,
        2,
        3};
    waretype->ReadDataFromBuf(BitOffset); //target call
    return 0;
}
