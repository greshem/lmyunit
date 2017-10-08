#include <unitcode/msrvcomm.h>

class MSrvCommRecvTable_SubClass: public MSrvCommRecvTable
{
public:
    MSrvCommRecvTable_SubClass():MSrvCommRecvTable(){}
};//MSrvCommRecvTable_SubClass

int main(int argc, char *argv[])
{
    MSrvCommRecvTable_SubClass* srvcommrecvtable = new MSrvCommRecvTable_SubClass(); //target call
    return 0;
}
