#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommRecvQueue* srvcommrecvqueue = new MSrvCommRecvQueue();
    srvcommrecvqueue->GetWaitRequestCount(); //target call
    return 0;
}
