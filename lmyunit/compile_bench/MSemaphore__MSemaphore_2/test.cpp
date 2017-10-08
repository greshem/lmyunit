#include <lmyunit/unitlib.h>

class MSemaphore_SubClass: public MSemaphore
{
public:
    MSemaphore_SubClass():MSemaphore(){}
};//MSemaphore_SubClass

int main(int argc, char *argv[])
{
    MSemaphore_SubClass* semaphore = new MSemaphore_SubClass(); //target call
    return 0;
}
