#include <unitcode/mdatetime.h>

class MDateTime_SubClass: public MDateTime
{
public:
    MDateTime_SubClass(unsigned short Year, unsigned short Month, unsigned short Day):MDateTime(Year, Month, Day){}
};//MDateTime_SubClass

int main(int argc, char *argv[])
{
    MDateTime_SubClass* datetime = new MDateTime_SubClass(2009, 11, 30); //target call
    return 0;
}
