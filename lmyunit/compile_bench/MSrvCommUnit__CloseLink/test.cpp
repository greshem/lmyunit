#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommUnit* srvcommunit = new MSrvCommUnit();
    srvcommunit->CloseLink(1, true); //target call
    return 0;
}
