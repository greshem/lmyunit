#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommRecvTable* srvcommrecvtable = new MSrvCommRecvTable();
    MSrvCommSubUnit* Parent = new MSrvCommSubUnit();
    srvcommrecvtable->Instance(Parent); //target call
    return 0;
}
