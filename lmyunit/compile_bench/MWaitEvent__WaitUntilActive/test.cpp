#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MWaitEvent* waitevent = new MWaitEvent();
    waitevent->WaitUntilActive(1); //target call
    return 0;
}
