#include <unitcode/mdatetime.h>

class MDateTime_SubClass: public MDateTime
{
public:
    MDateTime_SubClass(MDateTime const& In):MDateTime(In){}
};//MDateTime_SubClass

int main(int argc, char *argv[])
{
    MDateTime In(1);
    MDateTime_SubClass* datetime = new MDateTime_SubClass(In); //target call
    return 0;
}
