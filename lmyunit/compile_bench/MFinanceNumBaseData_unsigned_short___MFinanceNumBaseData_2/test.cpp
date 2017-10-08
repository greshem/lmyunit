#include <lmyunit/unitlib.h>

class MFinanceNumBaseData_unsigned_short__SubClass: public MFinanceNumBaseData<unsigned short>
{
public:
    MFinanceNumBaseData_unsigned_short__SubClass():MFinanceNumBaseData<unsigned short>(){}
};//MFinanceNumBaseData_unsigned_short__SubClass

int main(int argc, char *argv[])
{
    MFinanceNumBaseData_unsigned_short__SubClass* financenumbasedata = new MFinanceNumBaseData_unsigned_short__SubClass(); //target call
    return 0;
}
