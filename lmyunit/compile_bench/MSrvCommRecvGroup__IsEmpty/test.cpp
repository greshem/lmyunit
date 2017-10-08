#include <unitcode/msrvcomm.h>
int main(int argc, char *argv[])
{
    MSrvCommRecvGroup* srvcommrecvgroup = new MSrvCommRecvGroup();
    unsigned long* LinkNo = (unsigned long*) malloc(sizeof(unsigned long)*256);
    srvcommrecvgroup->IsEmpty(LinkNo); //target call
    return 0;
}
