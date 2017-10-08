#include <lmyunit/unitlib.h>

//auxiliary function
void*
ThreadFun(void* p1){
    return malloc(256);
}

int main(int argc, char *argv[])
{
    MThread* thread = new MThread();
    void* Param = malloc(256);
    thread->StartThread(
        "ThreadName",
        &ThreadFun,
        Param,
        true); //target call
    return 0;
}
