#include <lmyunit/unitlib.h>

class MFinanceNumBaseData_unsigned_char__SubClass: public MFinanceNumBaseData<unsigned char>
{
public:
    MFinanceNumBaseData_unsigned_char__SubClass():MFinanceNumBaseData<unsigned char>(){}
};//MFinanceNumBaseData_unsigned_char__SubClass

int main(int argc, char *argv[])
{
    MFinanceNumBaseData_unsigned_char__SubClass *financenumbasedata = new MFinanceNumBaseData_unsigned_char__SubClass();
    delete(financenumbasedata); //target call
    return 0;
}
