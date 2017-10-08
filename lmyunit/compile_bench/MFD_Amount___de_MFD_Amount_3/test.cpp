#include <lmyunit/unitlib.h>

class MFD_Amount_SubClass: public MFD_Amount
{
public:
    MFD_Amount_SubClass():MFD_Amount(){}
};//MFD_Amount_SubClass

int main(int argc, char *argv[])
{
    MFD_Amount_SubClass *amount = new MFD_Amount_SubClass();
    delete(amount); //target call
    return 0;
}
