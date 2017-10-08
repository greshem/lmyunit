#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommSubUnit *srvcommsubunit = new MSrvCommSubUnit();
    delete(srvcommsubunit); //target call
    return 0;
}
