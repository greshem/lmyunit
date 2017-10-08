#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceNumBaseData<long>* financenumbasedata = new MFinanceNumBaseData<long>();
    financenumbasedata->GetData(); //target call
    return 0;
}
