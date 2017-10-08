#include <lmyunit/unitlib.h>

class MSemaphore_MLock_SubClass: public MSemaphore::MLock
{
public:
    MSemaphore_MLock_SubClass(MSemaphore& sem, bool& rlt, unsigned long lTimeOut):MSemaphore::MLock(sem, rlt, lTimeOut){}
};//MSemaphore_MLock_SubClass

int main(int argc, char *argv[])
{
    MSemaphore sem;
    bool rlt = true;
    MSemaphore_MLock_SubClass* lock = new MSemaphore_MLock_SubClass(sem, (bool&)rlt, 1); //target call
    return 0;
}
