#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommAcceptQueue* srvcommacceptqueue = new MSrvCommAcceptQueue();
    srvcommacceptqueue->GetRuntimeClass(); //target call
    return 0;
}
