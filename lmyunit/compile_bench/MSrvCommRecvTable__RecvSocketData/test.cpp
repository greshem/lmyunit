#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommRecvTable* srvcommrecvtable = new MSrvCommRecvTable();
    srvcommrecvtable->RecvSocketData(1, 2, (long) 0); //target call
    return 0;
}
