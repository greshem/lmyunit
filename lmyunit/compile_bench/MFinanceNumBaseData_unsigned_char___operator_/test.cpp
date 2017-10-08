#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceNumBaseData<unsigned char>* financenumbasedata = new MFinanceNumBaseData<unsigned char>();
    financenumbasedata->operator=('A'); //target call
    return 0;
}
