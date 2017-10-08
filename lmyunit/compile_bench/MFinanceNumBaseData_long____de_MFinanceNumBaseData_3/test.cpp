#include <lmyunit/unitlib.h>

class MFinanceNumBaseData_long__SubClass: public MFinanceNumBaseData<long>
{
public:
    MFinanceNumBaseData_long__SubClass():MFinanceNumBaseData<long>(){}
};//MFinanceNumBaseData_long__SubClass

int main(int argc, char *argv[])
{
    MFinanceNumBaseData_long__SubClass *financenumbasedata = new MFinanceNumBaseData_long__SubClass();
    delete(financenumbasedata); //target call
    return 0;
}
