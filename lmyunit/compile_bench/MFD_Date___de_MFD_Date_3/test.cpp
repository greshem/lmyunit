#include <lmyunit/unitlib.h>

class MFD_Date_SubClass: public MFD_Date
{
public:
    MFD_Date_SubClass():MFD_Date(){}
};//MFD_Date_SubClass

int main(int argc, char *argv[])
{
    MFD_Date_SubClass *date = new MFD_Date_SubClass();
    delete(date); //target call
    return 0;
}
