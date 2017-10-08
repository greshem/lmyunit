#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MSemaphore* semaphore = new MSemaphore();
    semaphore->Lock(1); //target call
    return 0;
}
