#include <lmyunit/unitlib.h>

class MFinanceNumBaseData_double__SubClass: public MFinanceNumBaseData<double>
{
public:
    MFinanceNumBaseData_double__SubClass():MFinanceNumBaseData<double>(){}
};//MFinanceNumBaseData_double__SubClass

int main(int argc, char *argv[])
{
    MFinanceNumBaseData_double__SubClass* financenumbasedata = new MFinanceNumBaseData_double__SubClass(); //target call
    return 0;
}
