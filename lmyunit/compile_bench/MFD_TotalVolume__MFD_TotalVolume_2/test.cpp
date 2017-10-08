#include <lmyunit/unitlib.h>

class MFD_HighAmount_SubClass: public MFD_HighAmount
{
public:
    MFD_HighAmount_SubClass():MFD_HighAmount(){}
};//MFD_HighAmount_SubClass

int main(int argc, char *argv[])
{
    MFD_HighAmount_SubClass* totalvolume = new MFD_HighAmount_SubClass(); //target call
    return 0;
}
