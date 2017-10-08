#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommUnit* srvcommunit = new MSrvCommUnit();
    char IPAddr [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    srvcommunit->VerifyIP(IPAddr); //target call
    return 0;
}
