#include <lmyunit/unitlib.h>

class MFinanceBaseData_SubClass: public MFinanceBaseData
{
public:
    MFinanceBaseData_SubClass():MFinanceBaseData(){}
};//MFinanceBaseData_SubClass

int main(int argc, char *argv[])
{
    MFinanceBaseData_SubClass *financebasedata = new MFinanceBaseData_SubClass();
    delete(financebasedata); //target call
    return 0;
}
