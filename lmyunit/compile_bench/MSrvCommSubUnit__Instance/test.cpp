#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommSubUnit* srvcommsubunit = new MSrvCommSubUnit();
    MSrvCommUnit* Parent = new MSrvCommUnit();
    srvcommsubunit->Instance(1, Parent, 1); //target call
    return 0;
}
