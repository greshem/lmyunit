#include <lmyunit/unitlib.h>

class MOptionTree_SubClass: public MOptionTree
{
public:
    MOptionTree_SubClass():MOptionTree(){}
};//MOptionTree_SubClass

int main(int argc, char *argv[])
{
    MOptionTree_SubClass* optiontree = new MOptionTree_SubClass(); //target call
    return 0;
}
