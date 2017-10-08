#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_SignSubVolume* signsubvolume = new MFD_SignSubVolume();
    signsubvolume->operator=(1.5); //target call
    return 0;
}
