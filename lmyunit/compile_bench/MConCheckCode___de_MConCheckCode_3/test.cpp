#include <lmyunit/unitlib.h>

class MConCheckCode_SubClass: public MConCheckCode
{
public:
    MConCheckCode_SubClass():MConCheckCode(){}
};//MConCheckCode_SubClass

int main(int argc, char *argv[])
{
    MConCheckCode_SubClass *concheckcode = new MConCheckCode_SubClass();
    delete(concheckcode); //target call
    return 0;
}
