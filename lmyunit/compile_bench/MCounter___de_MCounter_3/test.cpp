#include <unitcode/mdatetime.h>

class MCounter_SubClass: public MCounter
{
public:
    MCounter_SubClass():MCounter(){}
};//MCounter_SubClass

int main(int argc, char *argv[])
{
    MCounter_SubClass *counter = new MCounter_SubClass();
    delete(counter); //target call
    return 0;
}
