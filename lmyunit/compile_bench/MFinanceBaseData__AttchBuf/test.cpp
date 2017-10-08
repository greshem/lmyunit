#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceBaseData* financebasedata = new MFinanceBaseData();
    char InBuf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    financebasedata->AttchBuf(InBuf, 4); //target call
    return 0;
}
