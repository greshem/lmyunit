#include <unitcode/mdatetime.h>

class MDateTime_SubClass: public MDateTime
{
public:
    MDateTime_SubClass(
        unsigned short Year,
        unsigned short Month,
        unsigned short Day,
        unsigned short Hour,
        unsigned short Min,
        unsigned short Sec):MDateTime(
            Year,
            Month,
            Day,
            Hour,
            Min,
            Sec){}
};//MDateTime_SubClass

int main(int argc, char *argv[])
{
    MDateTime_SubClass* datetime = new MDateTime_SubClass(
        2009,
        11,
        30,
        1,
        2,
        3); //target call
    return 0;
}
