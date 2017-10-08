#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommRecvQueue* srvcommrecvqueue = new MSrvCommRecvQueue();
    char InBuf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    srvcommrecvqueue->PutData(
        1,
        2,
        InBuf,
        4); //target call
    return 0;
}
