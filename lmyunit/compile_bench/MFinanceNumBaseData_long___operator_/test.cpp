#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceNumBaseData<long>* financenumbasedata = new MFinanceNumBaseData<long>();
    financenumbasedata->operator=(1L); //target call
    return 0;
}
