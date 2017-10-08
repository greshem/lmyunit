#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommRecvGroup* srvcommrecvgroup = new MSrvCommRecvGroup();
    srvcommrecvgroup->GetRuntimeClass(); //target call
    return 0;
}
