#include <lmyunit/unitlib.h>

class MResourceRecordSt_SubClass: public MResourceRecordSt
{
public:
    MResourceRecordSt_SubClass():MResourceRecordSt(){}
};//MResourceRecordSt_SubClass

int main(int argc, char *argv[])
{
    MResourceRecordSt_SubClass *resourcerecordst = new MResourceRecordSt_SubClass();
    delete(resourcerecordst); //target call
    return 0;
}
