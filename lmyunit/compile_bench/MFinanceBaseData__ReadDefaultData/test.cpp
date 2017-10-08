#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceBaseData* financebasedata = new MFinanceBaseData();
    unsigned long Offset [] = {
        0,
        1,
        2,
        3};
    financebasedata->ReadDefaultData(Offset); //target call
    return 0;
}
