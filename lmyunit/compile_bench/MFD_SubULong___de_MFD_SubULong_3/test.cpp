#include <lmyunit/unitlib.h>

class MFD_SubULong_SubClass: public MFD_SubULong
{
public:
    MFD_SubULong_SubClass():MFD_SubULong(){}
};//MFD_SubULong_SubClass

int main(int argc, char *argv[])
{
    MFD_SubULong_SubClass *subulong = new MFD_SubULong_SubClass();
    delete(subulong); //target call
    return 0;
}
