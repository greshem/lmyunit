#include <unitcode/msrvcomm.h>

class MSrvCommAcceptQueue_SubClass: public MSrvCommAcceptQueue
{
public:
    MSrvCommAcceptQueue_SubClass():MSrvCommAcceptQueue(){}
};//MSrvCommAcceptQueue_SubClass

int main(int argc, char *argv[])
{
    MSrvCommAcceptQueue_SubClass *srvcommacceptqueue = new MSrvCommAcceptQueue_SubClass();
    delete(srvcommacceptqueue); //target call
    return 0;
}
