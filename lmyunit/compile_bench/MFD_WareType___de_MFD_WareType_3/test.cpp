#include <lmyunit/unitlib.h>

class MFD_WareType_SubClass: public MFD_WareType
{
public:
    MFD_WareType_SubClass():MFD_WareType(){}
};//MFD_WareType_SubClass

int main(int argc, char *argv[])
{
    MFD_WareType_SubClass *waretype = new MFD_WareType_SubClass();
    delete(waretype); //target call
    return 0;
}
