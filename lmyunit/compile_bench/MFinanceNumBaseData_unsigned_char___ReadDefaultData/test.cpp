#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceNumBaseData<unsigned char>* financenumbasedata = new MFinanceNumBaseData<unsigned char>();
    unsigned long Offset [] = {
        0,
        1,
        2,
        3};
    financenumbasedata->ReadDefaultData(Offset); //target call
    return 0;
}
