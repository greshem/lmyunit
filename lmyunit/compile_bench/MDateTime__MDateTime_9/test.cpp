#include <unitcode/mdatetime.h>

class MDateTime_SubClass: public MDateTime
{
public:
    MDateTime_SubClass(unsigned long Date, unsigned long Time):MDateTime(Date, Time){}
};//MDateTime_SubClass

int main(int argc, char *argv[])
{
    MDateTime_SubClass* datetime = new MDateTime_SubClass(1, 1); //target call
    return 0;
}
