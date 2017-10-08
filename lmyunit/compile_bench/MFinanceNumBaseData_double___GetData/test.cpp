#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceNumBaseData<double>* financenumbasedata = new MFinanceNumBaseData<double>();
    financenumbasedata->GetData(); //target call
    return 0;
}
