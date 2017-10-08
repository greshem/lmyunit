#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceNumBaseData<char> *financenumbasedata = new MFinanceNumBaseData<char>();
    delete(financenumbasedata); //target call
    return 0;
}
