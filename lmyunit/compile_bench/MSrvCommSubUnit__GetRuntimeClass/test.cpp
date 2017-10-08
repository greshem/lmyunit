#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommSubUnit* srvcommsubunit = new MSrvCommSubUnit();
    srvcommsubunit->GetRuntimeClass(); //target call
    return 0;
}
