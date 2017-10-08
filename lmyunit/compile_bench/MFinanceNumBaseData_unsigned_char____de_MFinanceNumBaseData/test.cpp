#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceNumBaseData<unsigned char> *financenumbasedata = new MFinanceNumBaseData<unsigned char>();
    delete(financenumbasedata); //target call
    return 0;
}
