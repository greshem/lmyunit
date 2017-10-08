#include <lmyunit/unitlib.h>

class MSystemInfo_SubClass: public MSystemInfo
{
public:
    MSystemInfo_SubClass():MSystemInfo(){}
};//MSystemInfo_SubClass

int main(int argc, char *argv[])
{
    MSystemInfo_SubClass *systeminfo = new MSystemInfo_SubClass();
    delete(systeminfo); //target call
    return 0;
}
