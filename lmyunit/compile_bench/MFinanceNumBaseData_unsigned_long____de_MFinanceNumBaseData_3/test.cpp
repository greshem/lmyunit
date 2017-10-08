#include <lmyunit/unitlib.h>

class MFinanceNumBaseData_unsigned_long__SubClass: public MFinanceNumBaseData<unsigned long>
{
public:
    MFinanceNumBaseData_unsigned_long__SubClass():MFinanceNumBaseData<unsigned long>(){}
};//MFinanceNumBaseData_unsigned_long__SubClass

int main(int argc, char *argv[])
{
    MFinanceNumBaseData_unsigned_long__SubClass *financenumbasedata = new MFinanceNumBaseData_unsigned_long__SubClass();
    delete(financenumbasedata); //target call
    return 0;
}
