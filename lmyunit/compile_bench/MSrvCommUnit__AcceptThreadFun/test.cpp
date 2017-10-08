#include <unitcode/msrvcomm.h>

class MSrvCommUnit_SubClass: public MSrvCommUnit
{
public:
    MSrvCommUnit_SubClass():MSrvCommUnit(){}

    void* AcceptThreadFun_Wrapper() {
       void* In = malloc(256);
       return this->AcceptThreadFun(In);
    }
};//MSrvCommUnit_SubClass

int main(int argc, char *argv[])
{
    MSrvCommUnit_SubClass* srvcommunit = new MSrvCommUnit_SubClass();
    srvcommunit->AcceptThreadFun_Wrapper(); //target call
    return 0;
}
