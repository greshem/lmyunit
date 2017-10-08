#include <unitcode/msrvcomm.h>

class MSrvCommSendQueue_SubClass: public MSrvCommSendQueue
{
public:
    MSrvCommSendQueue_SubClass():MSrvCommSendQueue(){}
};//MSrvCommSendQueue_SubClass

int main(int argc, char *argv[])
{
    MSrvCommSendQueue_SubClass* srvcommsendqueue = new MSrvCommSendQueue_SubClass(); //target call
    return 0;
}
