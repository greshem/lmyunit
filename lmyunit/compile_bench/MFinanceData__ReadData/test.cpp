#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceData* financedata = new MFinanceData();
    char OutBuf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    financedata->ReadData(OutBuf, 4); //target call
    return 0;
}
