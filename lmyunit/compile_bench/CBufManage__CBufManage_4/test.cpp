#include <lmyunit/unitlib.h>

class CBufManage_SubClass: public CBufManage
{
public:
    CBufManage_SubClass():CBufManage(){}
};//CBufManage_SubClass

int main(int argc, char *argv[])
{
    CBufManage_SubClass* bufmanage = new CBufManage_SubClass(); //target call
    return 0;
}
