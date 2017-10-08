#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommLinkQueue* srvcommlinkqueue = new MSrvCommLinkQueue();
    char IPAddr [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    srvcommlinkqueue->AddLinkCount(
        (long) 0,
        1,
        IPAddr,
        2,
        3,
        (unsigned long) 0); //target call
    return 0;
}
