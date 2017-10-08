#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MWaitEvent *waitevent = new MWaitEvent();
    delete(waitevent); //target call
    return 0;
}
