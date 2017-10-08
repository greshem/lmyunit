#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
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
    MSrvCommUnit::SendSocketBlockFrame(
        (long) 0,
        &InHead,
        InBuf,
        8,
        (unsigned short) 0,
        (unsigned short) 0); //target call
    return 0;
}
