#include <lmyunit/unitlib.h>

class MFinanceBaseData_SubClass: public MFinanceBaseData
{
public:
    MFinanceBaseData_SubClass():MFinanceBaseData(){}

    void inner_getbit64_Wrapper() {
       unsigned long BitOffset [] = {
           0,
           1,
           2,
           3};
       unsigned long long Value [] = {
           0,
           1,
           2,
           3};
       this->inner_getbit64(BitOffset, Value, 4);
    }
};//MFinanceBaseData_SubClass

int main(int argc, char *argv[])
{
    MFinanceBaseData_SubClass* financebasedata = new MFinanceBaseData_SubClass();
    financebasedata->inner_getbit64_Wrapper(); //target call
    return 0;
}
