#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MSemaphore* semaphore = new MSemaphore();
    semaphore->UnLock(4); //target call
    return 0;
}
