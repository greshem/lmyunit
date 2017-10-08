#include <unitcode/msrvcomm.h>

class MSrvCommSendGroup_SubClass: public MSrvCommSendGroup
{
public:
    MSrvCommSendGroup_SubClass():MSrvCommSendGroup(){}
};//MSrvCommSendGroup_SubClass

int main(int argc, char *argv[])
{
    MSrvCommSendGroup_SubClass* srvcommsendgroup = new MSrvCommSendGroup_SubClass(); //target call
    return 0;
}
