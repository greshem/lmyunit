#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceNumBaseData<float> *financenumbasedata = new MFinanceNumBaseData<float>();
    delete(financenumbasedata); //target call
    return 0;
}
