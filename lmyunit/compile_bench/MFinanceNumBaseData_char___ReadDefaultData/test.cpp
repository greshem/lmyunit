#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceNumBaseData<char>* financenumbasedata = new MFinanceNumBaseData<char>();
    unsigned long Offset [] = {
        0,
        1,
        2,
        3};
    financenumbasedata->ReadDefaultData(Offset); //target call
    return 0;
}
