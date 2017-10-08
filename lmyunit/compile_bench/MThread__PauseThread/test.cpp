#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MThread* thread = new MThread();
    thread->PauseThread(); //target call
    return 0;
}
