#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommRecvQueue* srvcommrecvqueue = new MSrvCommRecvQueue();
    MSrvCommSubUnit* Parent = new MSrvCommSubUnit();
    srvcommrecvqueue->Instance(Parent); //target call
    return 0;
}
