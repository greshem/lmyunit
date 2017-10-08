#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceNumBaseData<long>* financenumbasedata = new MFinanceNumBaseData<long>();
    unsigned long Offset [] = {
        0,
        1,
        2,
        3};
    financenumbasedata->ReadDefaultData(Offset); //target call
    return 0;
}
