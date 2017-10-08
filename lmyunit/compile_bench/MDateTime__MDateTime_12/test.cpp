#include <unitcode/mdatetime.h>

class MDateTime_SubClass: public MDateTime
{
public:
    MDateTime_SubClass(
        unsigned short Hour,
        unsigned short Min,
        unsigned short Sec,
        unsigned short MSec):MDateTime(
            Hour,
            Min,
            Sec,
            MSec){}
};//MDateTime_SubClass

int main(int argc, char *argv[])
{
    MDateTime_SubClass* datetime = new MDateTime_SubClass(
        1,
        2,
        3,
        4); //target call
    return 0;
}
