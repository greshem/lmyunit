#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceNumBaseData<unsigned long>* financenumbasedata = new MFinanceNumBaseData<unsigned long>();
    financenumbasedata->GetData(); //target call
    return 0;
}
