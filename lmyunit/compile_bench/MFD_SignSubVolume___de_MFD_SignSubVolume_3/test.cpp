#include <lmyunit/unitlib.h>

class MFD_SignSubVolume_SubClass: public MFD_SignSubVolume
{
public:
    MFD_SignSubVolume_SubClass():MFD_SignSubVolume(){}
};//MFD_SignSubVolume_SubClass

int main(int argc, char *argv[])
{
    MFD_SignSubVolume_SubClass *signsubvolume = new MFD_SignSubVolume_SubClass();
    delete(signsubvolume); //target call
    return 0;
}
