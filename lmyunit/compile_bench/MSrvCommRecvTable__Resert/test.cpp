#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommRecvTable* srvcommrecvtable = new MSrvCommRecvTable();
    srvcommrecvtable->Resert(1, 2); //target call
    return 0;
}
