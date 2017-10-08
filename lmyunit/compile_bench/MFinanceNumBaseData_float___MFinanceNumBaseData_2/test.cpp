#include <lmyunit/unitlib.h>

class MFinanceNumBaseData_float__SubClass: public MFinanceNumBaseData<float>
{
public:
    MFinanceNumBaseData_float__SubClass():MFinanceNumBaseData<float>(){}
};//MFinanceNumBaseData_float__SubClass

int main(int argc, char *argv[])
{
    MFinanceNumBaseData_float__SubClass* financenumbasedata = new MFinanceNumBaseData_float__SubClass(); //target call
    return 0;
}
