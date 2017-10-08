#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommRecvTable* srvcommrecvtable = new MSrvCommRecvTable();
    srvcommrecvtable->GetRuntimeClass(); //target call
    return 0;
}
