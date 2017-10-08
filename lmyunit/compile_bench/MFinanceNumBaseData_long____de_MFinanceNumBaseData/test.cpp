#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceNumBaseData<long> *financenumbasedata = new MFinanceNumBaseData<long>();
    delete(financenumbasedata); //target call
    return 0;
}
