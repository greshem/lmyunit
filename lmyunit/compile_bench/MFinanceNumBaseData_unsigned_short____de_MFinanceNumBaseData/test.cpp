#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceNumBaseData<unsigned short> *financenumbasedata = new MFinanceNumBaseData<unsigned short>();
    delete(financenumbasedata); //target call
    return 0;
}
