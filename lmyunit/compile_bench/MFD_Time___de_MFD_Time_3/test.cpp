#include <lmyunit/unitlib.h>

class MFD_Time_SubClass: public MFD_Time
{
public:
    MFD_Time_SubClass():MFD_Time(){}
};//MFD_Time_SubClass

int main(int argc, char *argv[])
{
    MFD_Time_SubClass *mfd_time = new MFD_Time_SubClass();
    delete(mfd_time); //target call
    return 0;
}
