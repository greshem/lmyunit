#include <unitcode/mdatetime.h>

class MDateTime_SubClass: public MDateTime
{
public:
    MDateTime_SubClass(unsigned long In):MDateTime(In){}
};//MDateTime_SubClass

int main(int argc, char *argv[])
{
    MDateTime_SubClass *datetime = new MDateTime_SubClass(1);
    delete(datetime); //target call
    return 0;
}
