#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommRecvQueue* srvcommrecvqueue = new MSrvCommRecvQueue();
    srvcommrecvqueue->GetRuntimeClass(); //target call
    return 0;
}
