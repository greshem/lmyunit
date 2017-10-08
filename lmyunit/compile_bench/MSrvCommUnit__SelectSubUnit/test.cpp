#include <unitcode/msrvcomm.h>

class MSrvCommUnit_SubClass: public MSrvCommUnit
{
public:
    MSrvCommUnit_SubClass():MSrvCommUnit(){}

    int SelectSubUnit_Wrapper() {
       return this->SelectSubUnit();
    }
};//MSrvCommUnit_SubClass

int main(int argc, char *argv[])
{
    MSrvCommUnit_SubClass* srvcommunit = new MSrvCommUnit_SubClass();
    srvcommunit->SelectSubUnit_Wrapper(); //target call
    return 0;
}
