#include <lmyunit/unitlib.h>

class MFD_WareSerial_SubClass: public MFD_WareSerial
{
public:
    MFD_WareSerial_SubClass():MFD_WareSerial(){}
};//MFD_WareSerial_SubClass

int main(int argc, char *argv[])
{
    MFD_WareSerial_SubClass *wareserial = new MFD_WareSerial_SubClass();
    delete(wareserial); //target call
    return 0;
}
