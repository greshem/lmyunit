#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceNumBaseData<unsigned long> *financenumbasedata = new MFinanceNumBaseData<unsigned long>();
    delete(financenumbasedata); //target call
    return 0;
}
