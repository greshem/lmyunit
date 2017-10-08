#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommUnit* srvcommunit = new MSrvCommUnit();
    char OutBuf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    tagFrameHead InHead;
    MSrvCommUnit::RecvSocketFrame(
        (long) 0,
        &InHead,
        OutBuf,
        4);

    char InBuf [] = {
        'E',
        'F',
        'G',
        'H',
        '\0'};
    srvcommunit->SendFrame(
        1,
        &InHead,
        InBuf,
        4,
        1); //target call
    return 0;
}
