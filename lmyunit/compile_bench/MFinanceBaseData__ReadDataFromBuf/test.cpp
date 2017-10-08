#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceBaseData* financebasedata = new MFinanceBaseData();
    unsigned long BitOffset [] = {
        0,
        1,
        2,
        3};
    financebasedata->ReadDataFromBuf(BitOffset); //target call
    return 0;
}
