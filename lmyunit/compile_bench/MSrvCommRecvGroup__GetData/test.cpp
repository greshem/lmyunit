#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommRecvGroup* srvcommrecvgroup = new MSrvCommRecvGroup();
    tagFrameHead OutHead;
    char OutBuf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    srvcommrecvgroup->GetData(
        1,
        &OutHead,
        OutBuf,
        4); //target call
    return 0;
}
