#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_SignSubVolume* signsubvolume = new MFD_SignSubVolume();
    unsigned long BitOffset [] = {
        0,
        1,
        2,
        3};
    signsubvolume->WriteDataToBuf(BitOffset); //target call
    return 0;
}
