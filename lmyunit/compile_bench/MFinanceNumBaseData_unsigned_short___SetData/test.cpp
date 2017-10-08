#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceNumBaseData<unsigned short>* financenumbasedata = new MFinanceNumBaseData<unsigned short>();
    financenumbasedata->SetData(1); //target call
    return 0;
}
