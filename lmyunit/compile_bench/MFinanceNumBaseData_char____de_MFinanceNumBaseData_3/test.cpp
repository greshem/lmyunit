#include <lmyunit/unitlib.h>

class MFinanceNumBaseData_char__SubClass: public MFinanceNumBaseData<char>
{
public:
    MFinanceNumBaseData_char__SubClass():MFinanceNumBaseData<char>(){}
};//MFinanceNumBaseData_char__SubClass

int main(int argc, char *argv[])
{
    MFinanceNumBaseData_char__SubClass *financenumbasedata = new MFinanceNumBaseData_char__SubClass();
    delete(financenumbasedata); //target call
    return 0;
}
