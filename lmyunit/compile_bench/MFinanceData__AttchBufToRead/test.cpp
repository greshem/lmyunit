#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceData* financedata = new MFinanceData();
    char InBuf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    financedata->AttchBufToRead(InBuf, 4); //target call
    return 0;
}
