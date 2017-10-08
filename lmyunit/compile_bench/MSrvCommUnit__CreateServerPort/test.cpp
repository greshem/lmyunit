#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommUnit* srvcommunit = new MSrvCommUnit();
    unsigned short pListenPort [] = {
        0,
        1,
        2,
        3};
    unsigned long LinkNo [] = {
        0,
        1,
        2,
        3};
    srvcommunit->CreateServerPort(pListenPort, LinkNo, 4); //target call
    return 0;
}
