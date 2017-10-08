#include <unitcode/msrvcomm.h>

class MSrvCommUnit_SubClass: public MSrvCommUnit
{
public:
    MSrvCommUnit_SubClass():MSrvCommUnit(){}
};//MSrvCommUnit_SubClass

int main(int argc, char *argv[])
{
    MSrvCommUnit_SubClass* srvcommunit = new MSrvCommUnit_SubClass(); //target call
    return 0;
}
