#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    tagFrameHead OutHead;
    char OutBuf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    MSrvCommUnit::RecvSocketFrame(
        (long) 0,
        &OutHead,
        OutBuf,
        4); //target call
    return 0;
}
