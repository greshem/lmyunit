#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceNumBaseData<double>* financenumbasedata = new MFinanceNumBaseData<double>();
    financenumbasedata->operator=(1.5); //target call
    return 0;
}
