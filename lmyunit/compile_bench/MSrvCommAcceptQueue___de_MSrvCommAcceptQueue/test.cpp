#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommAcceptQueue *srvcommacceptqueue = new MSrvCommAcceptQueue();
    delete(srvcommacceptqueue); //target call
    return 0;
}
