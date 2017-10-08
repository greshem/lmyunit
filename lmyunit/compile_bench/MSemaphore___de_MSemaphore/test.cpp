#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MSemaphore *semaphore = new MSemaphore();
    delete(semaphore); //target call
    return 0;
}
