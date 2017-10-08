#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommRecvGroup *srvcommrecvgroup = new MSrvCommRecvGroup();
    delete(srvcommrecvgroup); //target call
    return 0;
}
