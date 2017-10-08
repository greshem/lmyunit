#include <lmyunit/unitlib.h>

class MFinanceData_SubClass: public MFinanceData
{
public:
    MFinanceData_SubClass():MFinanceData(){}
};//MFinanceData_SubClass

int main(int argc, char *argv[])
{
    MFinanceData_SubClass* financedata = new MFinanceData_SubClass(); //target call
    return 0;
}
