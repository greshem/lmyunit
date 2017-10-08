#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommRecvQueue* srvcommrecvqueue = new MSrvCommRecvQueue();
    tagFrameHead OutHead;
    char OutBuf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    srvcommrecvqueue->RecvFrame(
        1,
        &OutHead,
        OutBuf,
        4); //target call
    return 0;
}
