#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceNumBaseData<float>* financenumbasedata = new MFinanceNumBaseData<float>();
    financenumbasedata->operator=(1.5f); //target call
    return 0;
}
