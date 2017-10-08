#include <unitcode/msrvcomm.h>

class MSrvCommSubUnit_SubClass: public MSrvCommSubUnit
{
public:
    MSrvCommSubUnit_SubClass():MSrvCommSubUnit(){}
};//MSrvCommSubUnit_SubClass

int main(int argc, char *argv[])
{
    MSrvCommSubUnit_SubClass* srvcommsubunit = new MSrvCommSubUnit_SubClass(); //target call
    return 0;
}
