#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MSemaphore sem;
    bool rlt = true;
    MSemaphore::MLock lock(sem, (bool&)rlt);
    //target interface will be called at the end of main() function automatically
    return 0;
}
