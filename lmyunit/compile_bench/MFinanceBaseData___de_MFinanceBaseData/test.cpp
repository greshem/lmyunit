#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceBaseData *financebasedata = new MFinanceBaseData();
    delete(financebasedata); //target call
    return 0;
}
