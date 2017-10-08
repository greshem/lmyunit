#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommUnit* srvcommunit = new MSrvCommUnit();
    tagFrameHead OutHead;
    char OutBuf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    srvcommunit->RecvFrame(
        1,
        &OutHead,
        OutBuf,
        4); //target call
    return 0;
}
