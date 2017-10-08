#include <unitcode/msrvcomm.h>

class MSrvCommRecvGroup_SubClass: public MSrvCommRecvGroup
{
public:
    MSrvCommRecvGroup_SubClass():MSrvCommRecvGroup(){}
};//MSrvCommRecvGroup_SubClass

int main(int argc, char *argv[])
{
    MSrvCommRecvGroup_SubClass* srvcommrecvgroup = new MSrvCommRecvGroup_SubClass(); //target call
    return 0;
}
