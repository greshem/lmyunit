#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceData *financedata = new MFinanceData();
    delete(financedata); //target call
    return 0;
}
