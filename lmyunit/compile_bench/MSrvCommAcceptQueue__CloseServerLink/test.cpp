#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommAcceptQueue* srvcommacceptqueue = new MSrvCommAcceptQueue();
    srvcommacceptqueue->CloseServerLink(1); //target call
    return 0;
}
