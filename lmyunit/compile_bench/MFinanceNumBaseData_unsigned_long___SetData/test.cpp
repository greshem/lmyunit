#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceNumBaseData<unsigned long>* financenumbasedata = new MFinanceNumBaseData<unsigned long>();
    financenumbasedata->SetData(1); //target call
    return 0;
}
