#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MSemaphore sem;
    bool rlt = true;
    MSemaphore::MLock* lock = new MSemaphore::MLock(sem, (bool&)rlt, 1); //target call
    return 0;
}
