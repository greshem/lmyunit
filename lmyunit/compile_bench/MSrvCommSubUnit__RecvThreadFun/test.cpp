#include <unitcode/msrvcomm.h>

class MSrvCommSubUnit_SubClass: public MSrvCommSubUnit
{
public:
    MSrvCommSubUnit_SubClass():MSrvCommSubUnit(){}

    void* RecvThreadFun_Wrapper() {
       void* In = malloc(256);
       return this->RecvThreadFun(In);
    }
};//MSrvCommSubUnit_SubClass

int main(int argc, char *argv[])
{
    MSrvCommSubUnit_SubClass* srvcommsubunit = new MSrvCommSubUnit_SubClass();
    srvcommsubunit->RecvThreadFun_Wrapper(); //target call
    return 0;
}
