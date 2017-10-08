#include <lmyunit/unitlib.h>

class MFD_Bool_SubClass: public MFD_Bool
{
public:
    MFD_Bool_SubClass():MFD_Bool(){}
};//MFD_Bool_SubClass

int main(int argc, char *argv[])
{
    MFD_Bool_SubClass *mfd_bool = new MFD_Bool_SubClass();
    delete(mfd_bool); //target call
    return 0;
}
