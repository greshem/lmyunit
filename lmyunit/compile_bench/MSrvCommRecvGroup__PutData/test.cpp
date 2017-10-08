#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommRecvGroup* srvcommrecvgroup = new MSrvCommRecvGroup();
    char InBuf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    srvcommrecvgroup->PutData(1, InBuf, 4); //target call
    return 0;
}
