#include <unitcode/msrvcomm.h>

class MSrvCommUnit_SubClass: public MSrvCommUnit
{
public:
    MSrvCommUnit_SubClass():MSrvCommUnit(){}

    void UpdateSendSize_Wrapper() {
       this->UpdateSendSize(4);
    }
};//MSrvCommUnit_SubClass

int main(int argc, char *argv[])
{
    MSrvCommUnit_SubClass* srvcommunit = new MSrvCommUnit_SubClass();
    srvcommunit->UpdateSendSize_Wrapper(); //target call
    return 0;
}
