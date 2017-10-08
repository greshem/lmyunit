#include <unitcode/mdatetime.h>

class MDateTime_SubClass: public MDateTime
{
public:
    MDateTime_SubClass():MDateTime(){}
};//MDateTime_SubClass

int main(int argc, char *argv[])
{
    MDateTime_SubClass* datetime = new MDateTime_SubClass(); //target call
    return 0;
}
