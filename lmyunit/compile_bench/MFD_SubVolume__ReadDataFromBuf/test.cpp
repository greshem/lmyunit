#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_SubVolume* subvolume = new MFD_SubVolume();
    unsigned long BitOffset [] = {
        0,
        1,
        2,
        3};
    subvolume->ReadDataFromBuf(BitOffset); //target call
    return 0;
}
