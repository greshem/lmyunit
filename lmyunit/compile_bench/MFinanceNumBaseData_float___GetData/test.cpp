#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceNumBaseData<float>* financenumbasedata = new MFinanceNumBaseData<float>();
    financenumbasedata->GetData(); //target call
    return 0;
}
