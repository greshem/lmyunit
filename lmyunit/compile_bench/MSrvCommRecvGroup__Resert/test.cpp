#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommRecvGroup* srvcommrecvgroup = new MSrvCommRecvGroup();
    srvcommrecvgroup->Resert(1); //target call
    return 0;
}
