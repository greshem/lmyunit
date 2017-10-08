#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MWaitEvent* waitevent = new MWaitEvent();
    waitevent->Instance(); //target call
    return 0;
}
