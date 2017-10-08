#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceNumBaseData<unsigned short>* financenumbasedata = new MFinanceNumBaseData<unsigned short>();
    unsigned long Offset [] = {
        0,
        1,
        2,
        3};
    financenumbasedata->ReadDefaultData(Offset); //target call
    return 0;
}
