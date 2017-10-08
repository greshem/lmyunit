#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommRecvQueue *srvcommrecvqueue = new MSrvCommRecvQueue();
    delete(srvcommrecvqueue); //target call
    return 0;
}
