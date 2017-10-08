#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommAcceptQueue* srvcommacceptqueue = new MSrvCommAcceptQueue();
    tagSrvCommAcceptQueue Out;
    srvcommacceptqueue->GetSelectSocketInfo(&Out, 4); //target call
    return 0;
}
