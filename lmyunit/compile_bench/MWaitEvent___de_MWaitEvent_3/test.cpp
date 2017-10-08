#include <lmyunit/unitlib.h>

class MWaitEvent_SubClass: public MWaitEvent
{
public:
    MWaitEvent_SubClass():MWaitEvent(){}
};//MWaitEvent_SubClass

int main(int argc, char *argv[])
{
    MWaitEvent_SubClass *waitevent = new MWaitEvent_SubClass();
    delete(waitevent); //target call
    return 0;
}
