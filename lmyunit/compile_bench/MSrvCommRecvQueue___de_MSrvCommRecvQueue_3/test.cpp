#include <unitcode/msrvcomm.h>

class MSrvCommRecvQueue_SubClass: public MSrvCommRecvQueue
{
public:
    MSrvCommRecvQueue_SubClass():MSrvCommRecvQueue(){}
};//MSrvCommRecvQueue_SubClass

int main(int argc, char *argv[])
{
    MSrvCommRecvQueue_SubClass *srvcommrecvqueue = new MSrvCommRecvQueue_SubClass();
    delete(srvcommrecvqueue); //target call
    return 0;
}
