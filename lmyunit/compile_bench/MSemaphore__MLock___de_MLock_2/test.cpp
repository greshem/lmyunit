#include <lmyunit/unitlib.h>

class MSemaphore_MLock_SubClass: public MSemaphore::MLock
{
public:
    MSemaphore_MLock_SubClass(MSemaphore& sem, bool& rlt):MSemaphore::MLock(sem, rlt){}
};//MSemaphore_MLock_SubClass

int main(int argc, char *argv[])
{
    MSemaphore sem;
    bool rlt = true;
    MSemaphore_MLock_SubClass *lock = new MSemaphore_MLock_SubClass(sem, (bool&)rlt);
    delete(lock); //target call
    return 0;
}
