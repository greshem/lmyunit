#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceNumBaseData<unsigned long>* financenumbasedata = new MFinanceNumBaseData<unsigned long>();
    char* InBuf = (char*) malloc(sizeof(char)*256);
    unsigned long Offset [] = {
        0,
        1,
        2,
        3};
    financenumbasedata->WriteDefaultData(InBuf, Offset); //target call
    return 0;
}
