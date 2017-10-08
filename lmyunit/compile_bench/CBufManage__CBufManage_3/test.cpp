#include <lmyunit/unitlib.h>

class CBufManage_SubClass: public CBufManage
{
public:
    CBufManage_SubClass(int type):CBufManage(type){}
};//CBufManage_SubClass

int main(int argc, char *argv[])
{
    CBufManage_SubClass* bufmanage = new CBufManage_SubClass(0); //target call
    return 0;
}
