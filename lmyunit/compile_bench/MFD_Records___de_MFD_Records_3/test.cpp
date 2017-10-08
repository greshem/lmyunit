#include <lmyunit/unitlib.h>

class MFD_Records_SubClass: public MFD_Records
{
public:
    MFD_Records_SubClass():MFD_Records(){}
};//MFD_Records_SubClass

int main(int argc, char *argv[])
{
    MFD_Records_SubClass *records = new MFD_Records_SubClass();
    delete(records); //target call
    return 0;
}
