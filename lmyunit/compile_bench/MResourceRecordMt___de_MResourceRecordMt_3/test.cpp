#include <lmyunit/unitlib.h>

class MResourceRecordMt_SubClass: public MResourceRecordMt
{
public:
    MResourceRecordMt_SubClass():MResourceRecordMt(){}
};//MResourceRecordMt_SubClass

int main(int argc, char *argv[])
{
    MResourceRecordMt_SubClass *resourcerecordmt = new MResourceRecordMt_SubClass();
    delete(resourcerecordmt); //target call
    return 0;
}
