#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommRecvTable *srvcommrecvtable = new MSrvCommRecvTable();
    delete(srvcommrecvtable); //target call
    return 0;
}
