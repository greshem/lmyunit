#include <lmyunit/unitlib.h>

class MFD_SubVolume_SubClass: public MFD_SubVolume
{
public:
    MFD_SubVolume_SubClass():MFD_SubVolume(){}
};//MFD_SubVolume_SubClass

int main(int argc, char *argv[])
{
    MFD_SubVolume_SubClass *subvolume = new MFD_SubVolume_SubClass();
    delete(subvolume); //target call
    return 0;
}
