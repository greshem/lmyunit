#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommAcceptQueue* srvcommacceptqueue = new MSrvCommAcceptQueue();
    srvcommacceptqueue->Release(); //target call
    return 0;
}
