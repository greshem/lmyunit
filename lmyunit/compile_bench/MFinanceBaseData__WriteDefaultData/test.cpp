#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceBaseData* financebasedata = new MFinanceBaseData();
    char* InBuf = (char*) malloc(sizeof(char)*256);
    unsigned long Offset [] = {
        0,
        1,
        2,
        3};
    financebasedata->WriteDefaultData(InBuf, Offset); //target call
    return 0;
}
