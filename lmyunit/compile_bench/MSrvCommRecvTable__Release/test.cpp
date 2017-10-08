#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommRecvTable* srvcommrecvtable = new MSrvCommRecvTable();
    srvcommrecvtable->Release(); //target call
    return 0;
}
