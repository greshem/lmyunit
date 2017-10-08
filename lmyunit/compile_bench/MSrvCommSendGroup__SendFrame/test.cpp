#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommSendGroup* srvcommsendgroup = new MSrvCommSendGroup();
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
    srvcommsendgroup->SendFrame(
        1,
        &InHead,
        InBuf,
        4); //target call
    return 0;
}
