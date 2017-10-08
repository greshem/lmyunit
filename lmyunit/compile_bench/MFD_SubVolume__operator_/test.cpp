#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_SubVolume* subvolume = new MFD_SubVolume();
    subvolume->operator=(1.5); //target call
    return 0;
}
