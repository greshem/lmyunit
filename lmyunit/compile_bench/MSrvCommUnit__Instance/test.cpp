#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommUnit* srvcommunit = new MSrvCommUnit();
    srvcommunit->Instance(4, 1, 1); //target call
    return 0;
}
