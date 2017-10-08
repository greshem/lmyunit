#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFinanceNumBaseData<char>* financenumbasedata = new MFinanceNumBaseData<char>();
    financenumbasedata->GetData(); //target call
    return 0;
}
